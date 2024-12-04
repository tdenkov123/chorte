#ifndef BASEFB_H
#define BASEFB_H

#pragma once

#include <variant>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

class BaseFB {
public:
    using DataVariant = std::variant<bool, int, float, double, std::string>;

    virtual ~BaseFB() = default;
    virtual void execute() = 0;
    virtual std::string get_name() const = 0;
    virtual BaseFB* get_resource() { return; }
    
    const std::unordered_map<std::string, DataVariant>& get_data_inputs() const { return data_inputs; }
    const std::unordered_map<std::string, DataVariant>& get_data_outputs() const { return data_outputs; }
    const std::unordered_map<std::string, DataVariant>& get_event_inputs() const { return event_inputs; }
    const std::unordered_map<std::string, DataVariant>& get_event_outputs() const { return event_outputs; }

    void set_data_input(const std::string& key, const DataVariant& value) { data_inputs[key] = value; }
    void set_data_output(const std::string& key, const DataVariant& value) { data_outputs[key] = value; }
    void set_event_input(const std::string& key, const DataVariant& value) { event_inputs[key] = value; }
    void set_event_output(const std::string& key, const DataVariant& value) { event_outputs[key] = value; }
protected:
    explicit BaseFB(const std::string& _name) : name(_name) {}
private:
    std::string name;
    std::unordered_map<std::string, DataVariant> data_inputs;
    std::unordered_map<std::string, DataVariant> data_outputs;
    std::unordered_map<std::string, DataVariant> event_inputs;
    std::unordered_map<std::string, DataVariant> event_outputs;
};

#endif // BASEFB_H