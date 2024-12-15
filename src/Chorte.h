#ifndef CHORTE_H
#define CHORTE_H

#pragma once

#include "FBContainer.h"
#include "RuntimeEnvironment.h"
#include "FBootReader.h"
#include "TCPSockInet.h"

#include <argparse/argparse.hpp>

#include <thread>
#include <queue>

class Chorte {
private:
    FBContainer container;
    uint32_t runtime_frequency;

public:
    Chorte() {}
    ~Chorte() {}

    void init(int argc, char** argv);
    void run();
};


#endif // CHORTE_H