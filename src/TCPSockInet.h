#ifndef TCPSOCKETINET_H
#define TCPSOCKETINET_H

#pragma once

#include "BaseInet.h"

#include <string>

#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_connector.h>


class TCPSocketInet {
public:
    TCPSocketInet() {};
    virtual ~TCPSocketInet() {}; 

    bool connect();
    bool disconnect();

    std::string read();
    void write(const std::string& data);
private:
    std::string host;
    uint16_t port;
    sockpp::tcp_connector connector;
};



#endif // TCPSOCKETINET_H