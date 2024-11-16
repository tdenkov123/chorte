#include "RuntimeEnvironment.h"
#include <iostream>

RuntimeEnvironment::RuntimeEnvironment(FBContainer& fbContainer)
    : container(fbContainer) {}

void RuntimeEnvironment::process() {
    for (const auto& [id, block] : container.getAllBlocks()) {
        if (block) {
            block->processEvent("default_event");
            std::cout << "Block " << id << " processed. Value: " 
                      << block->getValue() << std::endl;
        }
    }

    try {
        auto startBlock = container.getStartBlock();
        std::cout << "Start block processed. Value: " << startBlock->getValue() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}