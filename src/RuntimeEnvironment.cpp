#include "RuntimeEnvironment.h"

RuntimeEnvironment::RuntimeEnvironment(FBContainer& fb_container) : container(fb_container) {}

RuntimeEnvironment::~RuntimeEnvironment() {
    if (_runtime_thread.joinable()) {
        _runtime_thread.join();
    }
}

void RuntimeEnvironment::run(uint32_t frequency) {
    _runtime_thread = std::thread(&RuntimeEnvironment::process, this, frequency);
}

void RuntimeEnvironment::process(uint32_t frequency) {
    std::queue<std::shared_ptr<BaseFB>> queue;
    auto start_fb = container.get_start_block();
    queue.push(start_fb);

    while (!queue.empty()) {
        auto current_fb = queue.front();
        queue.pop();

        current_fb->execute();
        std::cout << current_fb->get_name() << " executed\n";

        const auto& event_connections = container.get_event_connections();
        auto event_range = event_connections.equal_range(current_fb->get_name());

        for (auto it = event_range.first; it != event_range.second; ++it) {
            auto conn = it->second;
            auto next_fb = container.get_block(conn.to_fb);
            if (next_fb) {
                next_fb->set_event_input("REQ", true);
                current_fb->set_event_input("REQ", false);
                current_fb->set_event_input("CNF", false);
                queue.push(next_fb);
            }
        }

        const auto& data_connections = container.get_data_connections();
        auto data_range = data_connections.equal_range(current_fb->get_name());

        for (auto& it = data_range.first; it != data_range.second; ++it) {
            auto conn = it->second;
            auto next_fb = container.get_block(conn.to_fb);
            if (next_fb) {
                auto outputs = current_fb->get_data_outputs();
                if (outputs.size()) {
                    auto value = outputs.find(conn.from_port);
                    if (value != outputs.end()) next_fb->set_data_input(conn.to_port, value->second);
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(frequency));
    }
}
