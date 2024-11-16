<<<<<<< HEAD
#ifndef TCPSOCKINET_H
#define TCPSOCKINET_H
=======
#ifndef TCPSockInet_H
#define TCPSockInet_H
>>>>>>> 29050d7 (Add .h and .cpp files)

#pragma once

#include "BaseInet.h"

#include <string>
#include <exception>

#include <sockpp/tcp_socket.h>
#include <sockpp/tcp_connector.h>


<<<<<<< HEAD
class TCPSockInet {
public:
    TCPSockInet();
    virtual ~TCPSockInet();
=======
class TCPSockInet: public BaseInet {
public:
    TCPSockInet();
    virtual ~TCPSockInet(); 
>>>>>>> 29050d7 (Add .h and .cpp files)

    bool connect();
    bool disconnect();

    std::string read();
    void write(const std::string& data);
private:
    std::string host;
    uint16_t port;
    sockpp::tcp_connector connector;
};



<<<<<<< HEAD
#endif // TCPSOCKINET_H
=======
#endif // TCPSockInet_H
>>>>>>> 29050d7 (Add .h and .cpp files)
