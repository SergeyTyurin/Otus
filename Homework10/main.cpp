#include <iostream>
#include <thread>
#include "block.h"

int main(int argc, char** argv) {
    int n = std::atoi(argv[1]);
    Block b(n);
    std::string c;
    while(!std::getline(std::cin,c).eof())
    {
        b.writeCommands(c);

    }
    b.writeRestCommands();
    return 0;
}