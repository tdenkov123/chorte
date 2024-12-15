#ifndef FBOOTREADER_H
#define FBOOTREADER_H

#pragma once

#include "FBContainer.h"

#include <string>
#include <fstream>
#include <sstream>


class FBootReader {
private:
    FBContainer* container;

public:
    FBootReader(const std::string& filename, FBContainer& container);
    ~FBootReader();
    
    bool read_file(const std::string& filename);

};


#endif // FBOOTREADER_H