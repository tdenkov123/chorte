#ifndef FBCONTAINER_H
#define FBCONTAINER_H

#include "FunctionBlock.h"
#include <map>
#include <string>
#include <memory>

class FBContainer {
    std::map<std::string, std::shared_ptr<FunctionBlock>> blocks;

public:
    void addBlock(const std::string& id, std::shared_ptr<FunctionBlock> block) {
        blocks[id] = block;
    }

    void removeBlock(const std::string& id) {
        blocks.erase(id);
    }

    std::shared_ptr<FunctionBlock> getBlock(const std::string& id) const {
        auto it = blocks.find(id);
        return it != blocks.end() ? it->second : nullptr;
    }

    void createConnection(const std::string& from, const std::string& to) {
        // Logic for connection
    }

    void deleteConnection(const std::string& from, const std::string& to) {
        // Logic for disconnection
    }

    const auto& getAllBlocks() const { return blocks; }
};

#endif // FBCONTAINER_H