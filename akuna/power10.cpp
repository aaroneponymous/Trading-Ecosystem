#include <iostream>

// Primary template declaration
template<int N>
struct PowerOf10 {
    static constexpr int value = 10 * PowerOf10<N - 1>::value;
};

// Base case specialization
template<>
struct PowerOf10<0> {
    static constexpr int value = 1;
};

int main() {
    
    // Example usage
    std::cout << "10^0 = " << PowerOf10<0>::value << std::endl;
    std::cout << "10^1 = " << PowerOf10<1>::value << std::endl;
    std::cout << "10^2 = " << PowerOf10<2>::value << std::endl;
    std::cout << "10^3 = " << PowerOf10<3>::value << std::endl;
    std::cout << "10^4 = " << PowerOf10<4>::value << std::endl;

    return 0;
}
