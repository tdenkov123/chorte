#ifndef RUNTIMEENVIRONMENT_H
#define RUNTIMEENVIRONMENT_H

#include "FBContainer.h"

class RuntimeEnvironment {
    FBContainer& container;

public:
    RuntimeEnvironment(FBContainer& fb_container);

    void process();
};

#endif // RUNTIMEENVIRONMENT_H