#ifndef TCPSOCKINET_H
#define TCPSOCKINET_H

#pragma once

#include "BaseInet.h"

#include <string>
#include <exception>

#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_connector.h>


class TCPSockInet {
public:
    TCPSockInet();
    virtual ~TCPSockInet();

    bool connect();
    bool disconnect();

    std::string read();
    void write(const std::string& data);
private:
    std::string host;
    uint16_t port;
    sockpp::tcp_connector connector;
};



#endif // TCPSOCKINET_H