#include "Chorte.h"

void Chorte::init(int argc, char** argv) {
    argparse::ArgumentParser program("Chorte");
    program.add_argument("-f", "--file")
        .help("Path to the .fboot file")
        .required();
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

    this->runtime_frequency = std::atoi(program.get<std::string>("--frequency").c_str());
    std::string filename = program.get<std::string>("--file");
    FBootReader boot_reader(this->container);
    boot_reader.read_file(filename);
}

void Chorte::run() {
    RuntimeEnvironment runtime_env(this->container);
    runtime_env.run(this->runtime_frequency);
}