#include "FBContainer.h"
#include <stdexcept>

void FBContainer::add_block(const std::string& id, std::shared_ptr<BaseFB> block) {
    blocks[id] = block;
}

void FBContainer::remove_block(const std::string& id) {
    blocks.erase(id);
    if (start_block == id) {
        start_block.clear();
    }
}

std::shared_ptr<BaseFB> FBContainer::get_block(const std::string& id) const {
    auto it = blocks.find(id);
    return it != blocks.end() ? it->second : nullptr;
}

void FBContainer::create_connection(const std::string& from, const std::string& to) {
    std::string from_block_id = from.substr(0, from.find('.'));
    std::string from_port = from.substr(from.find('.'), from.size());
    std::string to_block_id = to.substr(0, to.find('.'));
    std::string to_port = to.substr(to.find('.'), to.size());

    connections[from_block_id] = to_block_id;
}

void FBContainer::delete_connection(const std::string& from, const std::string& to) {

}

const auto& FBContainer::get_all_blocks() const {
    return blocks;
}

void FBContainer::set_start_block(const std::string& id) {
    if (blocks.find(id) != blocks.end()) {
        start_block = id;
    } else {
        throw std::invalid_argument("Block with the given ID does not exist.");
    }
}

std::shared_ptr<BaseFB> FBContainer::get_start_block() const {
    if (start_block.empty()) {
        throw std::runtime_error("Start block is not set.");
    }

    auto it = blocks.find(start_block);
    if (it != blocks.end()) {
        return it->second;
    }

    throw std::runtime_error("Start block ID is set but not found in the container.");
}
