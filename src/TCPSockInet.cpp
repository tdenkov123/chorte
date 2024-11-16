#include "TCPSockInet.h"


TCPSockInet::TCPSockInet() {

}


TCPSockInet::~TCPSockInet() {
    
}


bool TCPSockInet::connect() {
    if (this->connector.connect(sockpp::inet_address(this->host, this->port), std::chrono::seconds(2))) {
        this->connector.read_timeout(std::chrono::seconds(1));
        return true;
    }
    return false;
}


bool TCPSockInet::disconnect() {
    if (this->connector.is_open()) {
        this->connector.close();
    }
    return true;
}


std::string TCPSockInet::read() {
    static const u_int16_t BUF_SIZE = 2048;
    std::string result;
    char buf[BUF_SIZE];
    u_char packet_header[3];
    if (!this->connector.is_connected()) throw std::runtime_error("[TCPSockInet] Socket is not open");

    int rc = connector.read(packet_header, 3);
    if (rc != 3) throw std::runtime_error("[TCPSockInet] Failed to read packet header");

    int32_t packet_size = ((int32_t) packet_header[1] << 8) + (int32_t) packet_header[2];
    while (packet_size > 0) {   
        int bytes_to_read = (packet_size > sizeof(buf)) ? sizeof(buf) : packet_size;
        int bytes_read = this->connector.read_n(buf, bytes_to_read);
        if (bytes_read <= 0) throw std::runtime_error("[TCPSockInet] Read error during data read.");
        result.append(buf, bytes_read);
        packet_size -= bytes_read;
    }
    return result;
}


void TCPSockInet::write(const std::string& data) {
    if (!this->connector.is_connected()) throw std::runtime_error("[TCPSockInet] Socket is not open");
    ssize_t res = this->connector.write_n(data.data(), data.size());
    if (res <= 0 || res != data.size()) throw std::runtime_error("[TCPSockInet] Write error during data write.");
}
