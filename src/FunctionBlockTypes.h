#ifndef FUNCTIONBLOCKTYPES_H
#define FUNCTIONBLOCKTYPES_H

#include "FunctionBlock.h"
#include <iostream>

template<typename data_type>
class BasicFunctionBlock : public FunctionBlock {
    data_type* data_inputs;
    data_type* data_outputs;
    std::string req;
    std::string cnf;

public:
    void processEvent(const std::string& event) override;
    std::string getValue() const override;
    void setValue(const std::string& value) override;
};

#endif // FUNCTIONBLOCKTYPES_H