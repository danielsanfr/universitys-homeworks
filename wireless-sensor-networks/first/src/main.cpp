#include "simulator.hpp"

int main(int argc, char *argv[])
{
    Simulator simulator(argc, argv);
    return simulator.execute();
}
