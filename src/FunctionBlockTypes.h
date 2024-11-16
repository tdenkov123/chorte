#ifndef FUNCTIONBLOCKTYPES_H
#define FUNCTIONBLOCKTYPES_H

#include "FunctionBlock.h"
#include <iostream>

class BasicFunctionBlock : public FunctionBlock {
    std::string value;

public:
    void processEvent(const std::string& event) override;
    std::string getValue() const override;
    void setValue(const std::string& value) override;
};

#endif // FUNCTIONBLOCKTYPES_H