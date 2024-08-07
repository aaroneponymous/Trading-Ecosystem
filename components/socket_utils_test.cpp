#include <iostream>
#include "socket_utils.h"

int main() {
    std::cout << Components::getIfaceIP("lo") << std::endl;
    std::cout << Components::getIfaceIP("wlp4s0") << std::endl;

    return 0;
}