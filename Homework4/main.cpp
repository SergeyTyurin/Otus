#include <vector>
#include <list>
#include <tuple>

#include "print.h"


int main() {
    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));

    print_ip(std::string("255.255.255.255"));
    print_ip(std::vector<int>{1,2,3,4});
    print_ip(std::list<int>{5,6,7,8});

    print_ip(std::make_tuple(10,20,30,40));

    return 0;
}