// RuntimeEnvironment.cpp
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

        // Enqueue connected function blocks
        for (const auto& connection : container.get_connections()) {
            if (connection.first == current_fb->get_name()) {
                auto next_fb = container.get_block(connection.second);
                if (next_fb) {
                    queue.push(next_fb);
                }
            }
        }
    }
}
