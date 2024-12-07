#include <iostream>
#include "RuntimeEnvironment.h"


int main(int argc, char* argv[]) {
    FBContainer container;
    container.add_block("START", std::make_shared<START>("START"));
    container.set_start_block("START");
    container.add_block("PrintFB", std::make_shared<PrintFB>("PrintFB"));
    container.create_connection("START", "PrintFB");

    RuntimeEnvironment runtime_env(container);
    runtime_env.run();

    return 0;
}