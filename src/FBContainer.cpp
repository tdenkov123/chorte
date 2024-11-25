#include "FBContainer.h"
#include <stdexcept>

void FBContainer::addBlock(const std::string& id, std::shared_ptr<BaseFB> block) {
    blocks[id] = block;
}

void FBContainer::removeBlock(const std::string& id) {
    blocks.erase(id);
    if (start_block == id) {
        start_block.clear();
    }
}

std::shared_ptr<BaseFB> FBContainer::getBlock(const std::string& id) const {
    auto it = blocks.find(id);
    return it != blocks.end() ? it->second : nullptr;
}

void FBContainer::createConnection(const std::string& from, const std::string& to) {
    
}

void FBContainer::deleteConnection(const std::string& from, const std::string& to) {

}

const auto& FBContainer::getAllBlocks() const {
    return blocks;
}

void FBContainer::setStartBlock(const std::string& id) {
    if (blocks.find(id) != blocks.end()) {
        start_block = id;
    } else {
        throw std::invalid_argument("Block with the given ID does not exist.");
    }
}

std::shared_ptr<BaseFB> FBContainer::getStartBlock() const {
    if (start_block.empty()) {
        throw std::runtime_error("Start block is not set.");
    }

    auto it = blocks.find(start_block);
    if (it != blocks.end()) {
        return it->second;
    }

    throw std::runtime_error("Start block ID is set but not found in the container.");
}
