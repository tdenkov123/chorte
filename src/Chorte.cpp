#include "Chorte.h"

void Chorte::init(int argc, char** argv) {
    argparse::ArgumentParser program("Chorte");
    program.add_argument("-f", "--file")
        .help("Path to the .fboot file")
        .required();
    program.add_argument("-h", "--host")
        .help("Host to open the socket on")
        .default_value(std::string("localhost"));
    program.add_argument("-p", "--port")
        .help("Port to open the socket on")
        .default_value(std::string("61499"))
        .action([](const std::string& value) { return std::stoi(value); });
    program.add_argument("-freq", "--frequency")
        .help("Frequency of the runtime environment in milliseconds")
        .default_value(std::string("50"))
        .action([](const std::string& value) { return std::stoi(value); });
    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }

    this->host = program.get<std::string>("--host");
    this->port = std::atoi(program.get<std::string>("--port").c_str());
    this->runtime_frequency = std::atoi(program.get<std::string>("--frequency").c_str());
    std::string filename = program.get<std::string>("--file");
    FBootReader boot_reader(this->container);
    boot_reader.read_file(filename);
}

void Chorte::run() {
    RuntimeEnvironment runtime_env(this->container);
    runtime_env.run(this->runtime_frequency);

    TCPSockInet sock_inet(this->host, this->port);
    XMLParser parser(this->container);
    sock_inet.connect();
    std::string resp;
    while (1) {
        try {
            std::string recv = sock_inet.read();
            if (recv.size() != 0) resp = parser.read_request(recv);
            if (resp.size() != 0) sock_inet.write(resp);
        } catch (const std::exception& e) {
            std::cerr << "[ERROR] Failed to read/write from/to socket: " << e.what() << std::endl;
        }
    }
}