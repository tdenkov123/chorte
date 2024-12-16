#ifndef CHORTE_H
#define CHORTE_H

#pragma once

#include "FBContainer.h"
#include "RuntimeEnvironment.h"
#include "FBootReader.h"
#include "TCPSockInet.h"
#include "XMLParser.h"

#include <argparse/argparse.hpp>

#include <thread>
#include <queue>

class Chorte {
private:
    FBContainer container;
    uint32_t runtime_frequency;

    std::string host;
    uint16_t port;

public:
    Chorte() {}
    ~Chorte() {}

    void init(int argc, char** argv);
    void run();
};


#endif // CHORTE_H