#ifndef RUNTIMEENVIRONMENT_H
#define RUNTIMEENVIRONMENT_H

#pragma once

#include "FBContainer.h"

#include <queue>
#include <thread>
#include <mutex>
#include <chrono>

class RuntimeEnvironment {
private:
    FBContainer& container;
    std::thread _runtime_thread;
public:
    explicit RuntimeEnvironment(FBContainer& fb_container);
    virtual ~RuntimeEnvironment();
    RuntimeEnvironment(const RuntimeEnvironment&) = delete;
    RuntimeEnvironment& operator=(const RuntimeEnvironment&) = delete;
    
    void process(uint32_t frequency);
    void run(uint32_t frequency);
};

#endif // RUNTIMEENVIRONMENT_H