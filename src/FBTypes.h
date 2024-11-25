#ifndef FBTYPES_H
#define FBTYPES_H

#pragma once

#include "BaseFB.h"

#include <iostream>
#include <type_traits>

class PrintFB: public BaseFB {
public:
    explicit PrintFB(const std::string& _name) : BaseFB(_name) {}
    void execute() override {
        for (const auto& input: data_inputs) {
            if (input) std::visit([](const auto& value) {std::cout << value << ' ';}, *input);
        }
        std::cout << '\n';
    }
    std::string get_name() const override { return "PrintFB"; }
};


class F_ADD: public BaseFB {
public:
    explicit F_ADD(const std::string& _name) : BaseFB(_name) {
        data_inputs.resize(2);
        data_outputs.resize(1);
    }
    void execute() override {
        std::visit([&](const auto& val1, const auto& val2) {
            if constexpr (std::is_arithmetic_v<decltype(val1)> && std::is_arithmetic_v<decltype(val2)>) {
                std::get<double>(*data_outputs[0]) = val1 + val2;
            } else std::cout << "F_ADD: Non-arithmetical input types\n";
        }, *data_inputs[0], *data_inputs[1]);
    }
    std::string get_name() const override { return "F_ADD"; }
};

#endif // FBTYPES_H
