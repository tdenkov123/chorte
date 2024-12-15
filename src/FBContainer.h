#ifndef FBCONTAINER_H
#define FBCONTAINER_H

#include "FBTypes.h"

#include <map>
#include <string>
#include <memory>
#include <vector>

struct Connection {
    bool is_event;
    std::string from_fb;
    std::string from_port;
    std::string to_fb;
    std::string to_port;
    Connection(bool _is_event, std::string& _from_fb, 
        std::string& _from_port, std::string& _to_fb, 
        std::string& _to_port) : is_event(_is_event), from_fb(_from_fb), 
                                from_port(_from_port), to_fb(_to_fb), to_port(_to_port) {}
    bool operator==(const Connection& comp) const {
        if (this->is_event == comp.is_event &&
            this->from_fb == comp.from_fb &&
            this->from_port == comp.from_port &&
            this->to_fb == comp.to_fb &&
            this->to_port == comp.to_port
        ) return true;
        return false;
    }
};


class FBContainer {
public:
    void add_block(const std::string& id, std::shared_ptr<BaseFB> block);
    void remove_block(const std::string& id);
    std::shared_ptr<BaseFB> get_block(const std::string& id) const;
    void create_data_connection(const std::string& from, const std::string& to);
    void create_event_connection(const std::string& from, const std::string& to);
    void delete_data_connection(const std::string& from, const std::string& to);
    void delete_event_connection(const std::string& from, const std::string& to);
    std::multimap<std::string, Connection> get_data_connections() const { return data_connections; };
    std::multimap<std::string, Connection> get_event_connections() const { return event_connections; };
    void force_value(const std::string& id, const std::string& port, const DataVariant& value);
    
    std::map<std::string, std::shared_ptr<BaseFB>> get_all_blocks() const { return blocks; }
    void set_start_block(const std::string& id);
    std::shared_ptr<BaseFB> get_start_block() const;
private:
    std::map<std::string, std::shared_ptr<BaseFB>> blocks;
    std::multimap<std::string, Connection> data_connections;
    std::multimap<std::string, Connection> event_connections;
    std::string start_block;
};

#endif // FBCONTAINER_H
