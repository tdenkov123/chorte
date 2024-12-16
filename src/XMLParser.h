#ifndef XMLPARSER_H
#define XMLPARSER_H

#pragma once

#include "FBContainer.h"

#include <pugixml.hpp>

#include <string>
#include <map>
#include <type_traits>

class XMLParser {
private:
    FBContainer* container;
public:
    explicit XMLParser(FBContainer& container);
    ~XMLParser();
    std::string generate_response(const std::string& action, uint32_t id);
    std::string read_request(const std::string& request);
};

#endif // XMLPARSER_H