#include "XMLParser.h"

XMLParser::XMLParser(FBContainer& container) : container(&container) {}

XMLParser::~XMLParser() {}

std::string XMLParser::generate_response(const std::string& action, const uint32_t id) {
    if (action == "READ") {
        std::string resp = "<Response ID=\"\"> <Watches> <Resource name=\"EMB_RES\">";
        auto blocks = container->get_all_blocks();
        for (auto& block: blocks) {
            resp.append("<FB name=\n");
            resp.append(block.second->get_name().c_str());
            resp.append("\">");
            auto event_inputs = block.second->get_event_inputs();
            auto event_outputs = block.second->get_event_outputs();
            auto data_inputs = block.second->get_data_inputs();
            auto data_outputs = block.second->get_data_outputs();
            for (auto& i: event_inputs) {
                resp.append("<Port name=\"");
                resp.append(i.first.c_str());
                resp.append("\"><Data value=\"");
                resp.append((i.second) ? "true" : "false");
                resp.append("\" forced=\"false\"/></Port>");
            }
            for (auto& i: event_outputs) {
                resp.append("<Port name=\"");
                resp.append(i.first.c_str());
                resp.append("\"><Data value=\"");
                resp.append((i.second) ? "true" : "false");
                resp.append("\" forced=\"false\"/></Port>");
            }
            for (auto& i: data_inputs) {
                resp.append("<Port name=\"");
                resp.append(i.first.c_str());
                resp.append("\"><Data value=\"");
                std::visit([&resp](const auto& val) {
                    using T = std::decay_t<decltype(val)>;
                    if constexpr (std::is_same_v<T, std::string>) {
                        resp.append(val);
                    } else if constexpr (std::is_same_v<T, bool>) {
                        resp.append(val ? "true" : "false");
                    } else {
                        resp.append(std::to_string(val));
                    }
                }, i.second);
                resp.append("\" forced=\"false\"/></Port>");
            }
            for (auto& i: data_outputs) {
                resp.append("<Port name=\"");
                resp.append(i.first.c_str());
                resp.append("\"><Data value=\"");
                std::visit([&resp](const auto& val) {
                    using T = std::decay_t<decltype(val)>;
                    if constexpr (std::is_same_v<T, std::string>) {
                        resp.append(val);
                    } else if constexpr (std::is_same_v<T, bool>) {
                        resp.append(val ? "true" : "false");
                    } else {
                        resp.append(std::to_string(val));
                    }
                }, i.second);
                resp.append("\" forced=\"false\"/></Port>");
            }
            resp.append("</FB>");
        }
        resp.append("</Resource> </Watches></Response>");
        return resp;
    } else {
        std::string resp = "<Response ID=\"";
        resp.append(std::to_string(id));
        resp.append("\" />");
        return resp;
    }
}

std::string XMLParser::read_request(const std::string& request) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(request.c_str());

    if (!result) {
        throw std::runtime_error("Failed to parse XML request");
    }

    pugi::xml_node request_node = doc.child("Request");
    if (!request_node) {
        throw std::runtime_error("Missing <Request> node");
    }

    std::string action = request_node.attribute("Action").as_string();
    if (action.empty()) {
        throw std::runtime_error("Missing Action attribute");
    }

    pugi::xml_attribute id_attr = request_node.attribute("ID");
    if (!id_attr) {
        throw std::runtime_error("Missing ID attribute");
    }
    uint32_t id = id_attr.as_uint();

    if (action == "CREATE") {
        if (pugi::xml_node fb_node = request_node.child("FB")) {
            std::string fb_name = fb_node.attribute("Name").as_string();
            std::string fb_type = fb_node.attribute("Type").as_string();

            std::shared_ptr<BaseFB> fb;
            if (fb_type == "INT2INT") {
                fb = std::make_shared<INT2INT>(fb_name);
            } else if (fb_type == "F_ADD") {
                fb = std::make_shared<F_ADD>(fb_name);
            } else if (fb_type == "START") {
                fb = std::make_shared<START>(fb_name);
                container->set_start_block(fb_name);
            } else if (fb_type == "PrintFB") {
                fb = std::make_shared<PrintFB>(fb_name);
            } else {
                throw std::runtime_error("Unknown FB type: " + fb_type);
            }
            container->add_block(fb_name, fb);
        } else if (pugi::xml_node conn_node = request_node.child("Connection")) {
            std::string source = conn_node.attribute("Source").as_string();
            std::string destination = conn_node.attribute("Destination").as_string();

            std::string source_port = source.substr(source.find('.') + 1);
            if (source_port == "CNF" || source_port == "REQ" || source_port == "WARM" || source_port == "COLD") {
                container->create_event_connection(source, destination);
            } else {
                container->create_data_connection(source, destination);
            }
        }
        return generate_response("CREATE", id);
    } else if (action == "WRITE") {
        if (pugi::xml_node conn_node = request_node.child("Connection")) {
            std::string source = conn_node.attribute("Source").as_string();
            std::string destination = conn_node.attribute("Destination").as_string();

            size_t dot_pos = destination.find('.');
            if (dot_pos != std::string::npos) {
                std::string fb_name = destination.substr(0, dot_pos);
                std::string port_name = destination.substr(dot_pos + 1);

                DataVariant value;
                if (source == "true" || source == "false") {
                    value = (source == "true");
                } else {
                    try {
                        value = std::stoi(source);
                    } catch (...) {
                        value = source;
                    }
                }

                container->force_value(fb_name, port_name, value);
                return generate_response("WRITE", id);
            }
        }
    } else if (action == "READ") {
        return generate_response("READ", id);
    }
    return "";
}