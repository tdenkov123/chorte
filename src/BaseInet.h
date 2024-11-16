#ifndef BASEINET_H
#define BASEINET_H

#pragma once

#include <string>

class BaseInet {
public:
    BaseInet() {};
    virtual ~BaseInet() {}; 
    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual std::string read() = 0;
    virtual void write(const std::string& data) = 0;
};



#endif // BASEINET_H