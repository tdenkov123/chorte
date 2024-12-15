#include <iostream>
#include "Chorte.h"

int main(int argc, char* argv[]) {
    Chorte chorte;
    chorte.init(argc, argv);
    chorte.run();

    return 0;
}