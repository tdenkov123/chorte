#ifndef FBCONTAINER_H
#define FBCONTAINER_H

#include "FBTypes.h"

#include <map>
#include <string>
#include <memory>

class FBContainer {
public:
    void add_block(const std::string& id, std::shared_ptr<BaseFB> block);
    void remove_block(const std::string& id);
    std::shared_ptr<BaseFB> get_block(const std::string& id) const;
    void create_connection(const std::string& from, const std::string& to);
    void delete_connection(const std::string& from, const std::string& to);
    const auto& get_all_blocks() const { return blocks; }
    void set_start_block(const std::string& id);
    std::shared_ptr<BaseFB> get_start_block() const;
private:
    std::map<std::string, std::shared_ptr<BaseFB>> blocks;
    std::map<std::string, std::string> connections;
    std::string start_block;
};

#endif // FBCONTAINER_H
