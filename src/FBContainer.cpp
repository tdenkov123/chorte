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

void FBContainer::create_data_connection(const std::string& from, const std::string& to) {
    auto pos_from = from.find('.');
    auto pos_to = to.find('.');
    std::string from_fb = from.substr(0, pos_from);
    std::string from_port = from.substr(pos_from + 1);
    std::string to_fb = to.substr(0, pos_to);
    std::string to_port = to.substr(pos_to + 1);

    data_connections.insert({from, to});
}

void FBContainer::create_event_connection(const std::string& from, const std::string& to) {
    auto pos_from = from.find('.');
    auto pos_to = to.find('.');
    std::string from_fb = from.substr(0, pos_from);
    std::string from_port = from.substr(pos_from + 1);
    std::string to_fb = to.substr(0, pos_to);
    std::string to_port = to.substr(pos_to + 1);

    event_connections.insert({from, to});
}

void FBContainer::delete_data_connection(const std::string& from, const std::string& to) {
    auto range = data_connections.equal_range(from);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == to) {
            data_connections.erase(it);
            break;
        }
    }
}

void FBContainer::delete_event_connection(const std::string& from, const std::string& to) {
    auto range = event_connections.equal_range(from);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == to) {
            event_connections.erase(it);
            break;
        }
    }
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
