#include <iostream>
#include "RuntimeEnvironment.h"


int main(int argc, char* argv[]) {
    FBContainer container;
    container.add_block("START", std::make_shared<START>("START"));
    container.set_start_block("START");

    container.add_block("INT2INT", std::make_shared<INT2INT>("INT2INT"));
    container.add_block("INT2INT_1", std::make_shared<INT2INT>("INT2INT_1"));
    container.add_block("F_ADD", std::make_shared<F_ADD>("F_ADD"));
    container.add_block("PRINT", std::make_shared<PrintFB>("PRINT"));

    container.create_event_connection("START.CNF", "INT2INT.REQ");
    container.create_event_connection("INT2INT.CNF", "INT2INT_1.REQ");
    container.create_event_connection("INT2INT_1.CNF", "F_ADD.REQ");
    container.create_event_connection("F_ADD.CNF", "PRINT.REQ");

    container.create_data_connection("INT2INT.OUT", "F_ADD.IN1");
    container.create_data_connection("INT2INT_1.OUT", "F_ADD.IN2");
    container.create_data_connection("F_ADD.OUT", "PRINT.IN");    

    RuntimeEnvironment runtime_env(container);
    runtime_env.run();

    return 0;
}