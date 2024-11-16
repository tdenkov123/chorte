#ifndef FUNCTIONBLOCK_H
#define FUNCTIONBLOCK_H

#include <string>

class FunctionBlock {
public:
    virtual ~FunctionBlock() = default;

    virtual void processEvent(const std::string& event) = 0;
    virtual std::string getValue() const = 0;
    virtual void setValue(const std::string& value) = 0;
};

#endif // FUNCTIONBLOCK_H