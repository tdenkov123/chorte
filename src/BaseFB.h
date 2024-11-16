#ifndef BASEFB_H
#define BASEFB_H

#pragma once

#include <string>



class BaseFB {
public:
    BaseFB(const std::string& _name, const std::string _type) : name(_name), type(_type)  {}
    virtual ~BaseFB() {};

private:
    std::string name;
    std::string type;
};


#endif // BASEFB_H