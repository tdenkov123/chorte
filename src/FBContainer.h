#ifndef FBCONTAINER_H
#define FBCONTAINER_H

#include "FBTypes.h"

#include <map>
#include <string>
#include <memory>

class FBContainer {
public:
    void addBlock(const std::string& id, std::shared_ptr<BaseFB> block);
    void removeBlock(const std::string& id);
    std::shared_ptr<BaseFB> getBlock(const std::string& id) const;
    void createConnection(const std::string& from, const std::string& to);
    void deleteConnection(const std::string& from, const std::string& to);
    const auto& getAllBlocks() const { return blocks; }
    void setStartBlock(const std::string& id);
    std::shared_ptr<BaseFB> getStartBlock() const;
private:
    std::map<std::string, std::shared_ptr<BaseFB>> blocks;
    std::string start_block;
};

#endif // FBCONTAINER_H
