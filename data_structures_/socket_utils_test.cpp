#include <iostream>
#include "socket_utils.h"

int main() {
    std::cout << Common::getIfaceIP("lo") << std::endl;
    std::cout << Common::getIfaceIP("wlp4s0") << std::endl;

    return 0;
}