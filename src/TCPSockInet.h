#ifndef TCPSOCKINET_H
#define TCPSOCKINET_H

#pragma once

#include "BaseInet.h"

#include <string>
#include <exception>
#include <thread>

#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_connector.h>
#include <sockpp/tcp_acceptor.h>
#include <sockpp/tcp_socket.h>
#include <sockpp/inet_address.h>


class TCPSockInet: public BaseInet {
public:
    TCPSockInet(std::string host, uint16_t port, FBContainer& container);
    virtual ~TCPSockInet(); 

    bool connect();
    bool disconnect();
    void server_loop();

    std::string read();
    void write(const std::string& data);
private:
    FBContainer* container;
    XMLParser parser;
    bool running;
    std::string host;
    uint16_t port;
    sockpp::tcp_acceptor acceptor;
    sockpp::tcp_socket client_sock;
};



#endif // TCPSOCKINET_H
