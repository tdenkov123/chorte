#include "FBootReader.h"

FBootReader::FBootReader(const std::string& filename, FBContainer& container) : container(&container) {
    read_file(filename);
}

FBootReader::~FBootReader() {
}

bool FBootReader::read_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    container->add_block("START", std::make_shared<START>("START"));
    container->set_start_block("START");

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        size_t semicolon_pos = line.find(';');
        std::string request_str;
        if (semicolon_pos != std::string::npos) {
            request_str = line.substr(semicolon_pos + 1);
        } else {
            request_str = line;
        }

        size_t action_pos = request_str.find("Action=\"");
        if (action_pos == std::string::npos) {
            continue;
        }
        action_pos += 8;
        size_t action_end = request_str.find('"', action_pos);
        std::string action = request_str.substr(action_pos, action_end - action_pos);

        if (action == "CREATE") {
            if (request_str.find("<FB") != std::string::npos) {
                size_t name_pos = request_str.find("Name=\"");
                size_t name_end = request_str.find('"', name_pos + 6);
                std::string fb_name = request_str.substr(name_pos + 6, name_end - name_pos - 6);

                size_t type_pos = request_str.find("Type=\"");
                size_t type_end = request_str.find('"', type_pos + 6);
                std::string fb_type = request_str.substr(type_pos + 6, type_end - type_pos - 6);

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
                    continue;
                }
                container->add_block(fb_name, fb);
            }

            else if (request_str.find("<Connection") != std::string::npos) {
                size_t source_pos = request_str.find("Source=\"");
                size_t source_end = request_str.find('"', source_pos + 8);
                std::string source = request_str.substr(source_pos + 8, source_end - source_pos - 8);

                size_t dest_pos = request_str.find("Destination=\"");
                size_t dest_end = request_str.find('"', dest_pos + 13);
                std::string destination = request_str.substr(dest_pos + 13, dest_end - dest_pos - 13);

                std::string source_port = source.substr(source.find('.') + 1);
                if (source_port == "CNF" || source_port == "REQ" || source_port == "WARM" || source_port == "COLD") {
                    container->create_event_connection(source, destination);
                } else {
                    container->create_data_connection(source, destination);
                }
            }
        } else if (action == "WRITE") {
            if (request_str.find("<Connection") != std::string::npos) {
                size_t source_start = request_str.find("Source=\"") + 8;
                size_t source_end = request_str.find('"', source_start);
                std::string source_value = request_str.substr(source_start, source_end - source_start);

                size_t dest_start = request_str.find("Destination=\"") + 13;
                size_t dest_end = request_str.find('"', dest_start);
                std::string destination = request_str.substr(dest_start, dest_end - dest_start);

                size_t dot_pos = destination.find('.');
                std::string fb_name = destination.substr(0, dot_pos);
                std::string port_name = destination.substr(dot_pos + 1);

                auto fb = container->get_block(fb_name);
                if (fb) {
                    DataVariant value;
                    if (source_value == "true" || source_value == "false") {
                        value = (source_value == "true");
                    } else {
                        try {
                            size_t pos;
                            int int_value = std::stoi(source_value, &pos);
                            if (pos == source_value.size()) {
                                value = int_value;
                            } else {
                                float float_value = std::stof(source_value, &pos);
                                if (pos == source_value.size()) {
                                    value = float_value;
                                } else {
                                    value = source_value;
                                }
                            }
                        } catch (...) {
                            value = source_value;
                        }
                    }
                    container->force_value(fb_name, port_name, value);
                }
            }
        } else if (action == "START") {
            return true;
        }
    }
    return false;
}
