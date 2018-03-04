#include <iostream>
#include "block.h"

int main() {
    int n;
    std::cin>>n;
    Block b(n);
    std::string c;
    while(std::cin>>c)
    {
        b.writeCommands(c);
    }
    return 0;
}