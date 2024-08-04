#include <cstdio>
#include <cstdint>

// Compiler Instruction: g++ -S -Wall -o3 4_tail_call.cpp

auto __attribute__ ((noinline)) factorial(unsigned n) ->
    unsigned {
        return (n ? n * factorial(n - 1) : 1);
}

int main() {
    [[maybe_unused]] volatile auto res = factorial(100);
    return 0;
}



