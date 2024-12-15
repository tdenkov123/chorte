#ifndef FBTYPES_H
#define FBTYPES_H

#pragma once

#include "BaseFB.h"

#include <iostream>
#include <type_traits>


class START: public BaseFB {
public:
    explicit START(const std::string& _name) : BaseFB(_name) {
        set_event_output("WARM", false);
        set_event_output("COLD", false);
    }
    void execute() override {}
};


class PrintFB: public BaseFB {
public:
    explicit PrintFB(const std::string& _name) : BaseFB(_name) {
        set_data_input("IN", 0);

        set_event_input("REQ", false);
        set_event_output("CNF", false);
    }
    void execute() override {
        auto val = get_data_inputs().at("IN");
        std::visit([](const auto& val) { std::cout << val; }, val);
        std::cout << '\n';
    }
};


class F_ADD: public BaseFB {
public:
    explicit F_ADD(const std::string& _name) : BaseFB(_name) {
        set_data_input("IN1", 0);
        set_data_input("IN2", 0);
        set_data_output("OUT", 0);

        set_event_input("REQ", false);
        set_event_output("CNF", false);
    }
    void execute() override {
        auto in1 = std::get<int>(get_data_inputs().at("IN1"));
        auto in2 = std::get<int>(get_data_inputs().at("IN2"));
        set_data_output("OUT", in1 + in2);
    }
};


class INT2INT: public BaseFB {
public:
    explicit INT2INT(const std::string& _name) : BaseFB(_name) {
        set_data_input("IN", 1);
        set_data_output("OUT", 0);

        set_event_input("REQ", false);
        set_event_output("CNF", false);
    }
    void execute() override {
        auto in = std::get<int>(get_data_inputs().at("IN"));
        set_data_output("OUT", in);
    }
};


#endif // FBTYPES_H
