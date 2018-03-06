#include <iostream>
#include "block.h"

int main(int argc, char** argv) {
    int n = std::atoi(argv[1]);
    Block b(n);
    std::string c;
    while(std::cin>>c)
    {
        b.writeCommands(c);
    }
    return 0;
}