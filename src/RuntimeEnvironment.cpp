#include "RuntimeEnvironment.h"

RuntimeEnvironment::RuntimeEnvironment(FBContainer& fb_container) : container(fb_container) {}

RuntimeEnvironment::~RuntimeEnvironment() {
    if (_runtime_thread.joinable()) {
        _runtime_thread.join();
    }
}

void RuntimeEnvironment::run() {
    _runtime_thread = std::thread(&RuntimeEnvironment::process, this);
}

void RuntimeEnvironment::process() {
    std::queue<std::shared_ptr<BaseFB>> queue;
    auto start_fb = container.get_start_block();
    queue.push(start_fb);

    while (!queue.empty()) {
        auto current_fb = queue.front();
        queue.pop();


        current_fb->execute();
        std::cout << current_fb->get_name() << " executed\n";

        for (const auto& [from, to] : container.get_connections()) {
            auto pos_from = from.find('.');
            auto pos_to = to.find('.');
            std::string from_fb = from.substr(0, pos_from);
            std::string from_port = from.substr(pos_from + 1);
            std::string to_fb = to.substr(0, pos_to);
            std::string to_port = to.substr(pos_to + 1);

            if (from_fb == current_fb->get_name()) {
                auto next_fb = container.get_block(to_fb);
                if (next_fb) {
                    if (current_fb->get_event_outputs().count(from_port)) {
                        bool req = current_fb->get_event_outputs().at(from_port);
                        if (req) {
                            current_fb->set_event_input("REQ", false);
                            current_fb->set_event_output("CNF", true);
                        }
                    }
                    if (current_fb->get_data_outputs().count(from_port)) {
                        auto value = current_fb->get_data_outputs().at(from_port);
                        next_fb->set_data_input(to_port, value);
                    }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                queue.push(next_fb);
                }
            }
        }
    }
}
