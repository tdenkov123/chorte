#include "FunctionBlockTypes.h"

void BasicFunctionBlock::processEvent(const std::string& event) {
    std::cout << "Processing event: " << event << std::endl;
}

std::string BasicFunctionBlock::getValue() const {
    return value;
}

void BasicFunctionBlock::setValue(const std::string& value) {
    this->value = value;
}