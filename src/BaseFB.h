#ifndef BASEFB_H
#define BASEFB_H

#pragma once

#include <variant>
#include <string>
#include <vector>
#include <functional>

class BaseFB {
public:
    using DataVariant = std::variant<bool, int, float, double, std::string>;

    virtual ~BaseFB() = default;
    virtual void execute() = 0;
    virtual std::string get_name() const = 0;

    std::vector<DataVariant*> data_inputs;
    std::vector<DataVariant*> data_outputs;

    std::vector<std::function<void()>> event_inputs;
    std::vector<std::function<void()>> event_outputs;

protected:
    explicit BaseFB(const std::string& _name) : name(_name) {}
private:
    std::string name;
};

#endif // BASEFB_H