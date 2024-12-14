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
    void create_data_connection(const std::string& from, const std::string& to);
    void create_event_connection(const std::string& from, const std::string& to);
    void delete_data_connection(const std::string& from, const std::string& to);
    void delete_event_connection(const std::string& from, const std::string& to);
    std::multimap<std::string, std::string> get_data_connections() const { return data_connections; };
    std::multimap<std::string, std::string> get_event_connections() const { return event_connections; };
    
    std::map<std::string, std::shared_ptr<BaseFB>> get_all_blocks() const { return blocks; }
    void set_start_block(const std::string& id);
    std::shared_ptr<BaseFB> get_start_block() const;
private:
    std::map<std::string, std::shared_ptr<BaseFB>> blocks;
    std::multimap<std::string, std::string> data_connections;
    std::multimap<std::string, std::string> event_connections;
    std::string start_block;
};

#endif // FBCONTAINER_H
