#include "FBContainer.h"
#include <stdexcept>

void FBContainer::addBlock(const std::string& id, std::shared_ptr<FunctionBlock> block) {
    blocks[id] = block;
}

void FBContainer::removeBlock(const std::string& id) {
    blocks.erase(id);
    if (startBlockId == id) {
        startBlockId.clear(); // Очистка, если удалён стартовый блок
    }
}

std::shared_ptr<FunctionBlock> FBContainer::getBlock(const std::string& id) const {
    auto it = blocks.find(id);
    return it != blocks.end() ? it->second : nullptr;
}

void FBContainer::createConnection(const std::string& from, const std::string& to) {
    // Logic for connection (заглушка для дальнейшей реализации)
}

void FBContainer::deleteConnection(const std::string& from, const std::string& to) {
    // Logic for disconnection (заглушка для дальнейшей реализации)
}

const auto& FBContainer::getAllBlocks() const {
    return blocks;
}

void FBContainer::setStartBlock(const std::string& id) {
    if (blocks.find(id) != blocks.end()) {
        startBlockId = id;
    } else {
        throw std::invalid_argument("Block with the given ID does not exist.");
    }
}

std::shared_ptr<FunctionBlock> FBContainer::getStartBlock() const {
    if (startBlockId.empty()) {
        throw std::runtime_error("Start block is not set.");
    }

    auto it = blocks.find(startBlockId);
    if (it != blocks.end()) {
        return it->second;
    }

    throw std::runtime_error("Start block ID is set but not found in the container.");
}