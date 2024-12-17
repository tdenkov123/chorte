#include "TCPSockInet.h"


TCPSockInet::TCPSockInet(std::string host, uint16_t port, FBContainer& container): host(host), port(port), 
        acceptor(sockpp::inet_address(host, port)), container(&container), parser(container) {
    sockpp::initialize();
}

TCPSockInet::~TCPSockInet() {
    disconnect();
    acceptor.close();
}

bool TCPSockInet::connect() {
    if (!acceptor) {
        std::cerr << "Error creating the acceptor: " << acceptor.last_error_str() << std::endl;
        return false;
    }
    if (!acceptor.listen()) {
        std::cerr << "Error listening on port: " << port << " - " 
                  << acceptor.last_error_str() << std::endl;
        return false;
    }
    std::cout << "Server listening on " << host << ":" << port << std::endl;
    return true;
}

void TCPSockInet::server_loop() {
    running = true;
    while (running) {
        client_sock = acceptor.accept();
        if (!client_sock) {
            std::cerr << "Error accepting client connection: " << acceptor.last_error_str() << std::endl;
            continue;
        }
        std::cout << "Client connected: " << client_sock.peer_address().to_string() << std::endl;

        std::string msg = read();
        if (msg.size() > 0) {
            std::cout << "Received: " << msg << std::endl;
            std::string response = parser.read_request(msg);
            if (response.size() > 0) write(response);
        }
    }
    disconnect();
}

bool TCPSockInet::disconnect() {
    if (client_sock) {
        client_sock.close();
        std::cout << "Client disconnected" << std::endl;
    }
    return true;
}

std::string TCPSockInet::read() {
    static const u_int16_t BUF_SIZE = 2048;
    std::string result;
    char buf[BUF_SIZE];
    u_char packet_header[3];
    int rc = client_sock.read(packet_header, 3);
    if (rc != 3) throw std::runtime_error("[TCPSockInet] Failed to read packet header");

    int32_t packet_size = ((int32_t) packet_header[1] << 8) + (int32_t) packet_header[2];
    while (packet_size > 0) {   
        int bytes_to_read = (packet_size > sizeof(buf)) ? sizeof(buf) : packet_size;
        int bytes_read = this->client_sock.read_n(buf, bytes_to_read);
        if (bytes_read <= 0) throw std::runtime_error("[TCPSockInet] Read error during data read.");
        result.append(buf, bytes_read);
        packet_size -= bytes_read;
    }
    return result;
}


void TCPSockInet::write(const std::string& data) {
    ssize_t res = this->client_sock.write_n(data.data(), data.size());
    if (res <= 0 || res != data.size()) throw std::runtime_error("[TCPSockInet] Write error during data write.");
}
