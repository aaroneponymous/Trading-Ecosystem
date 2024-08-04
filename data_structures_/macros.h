#pragma once

#include <cstring>
#include <iostream>

// Macros for Branch Prediction Hints to the Compiler

// C++ 20 Standard:
// #if __cplusplus >= 202002L // Check if the C++20 standard is supported
// #define LIKELY(x) (x) [[likely]]
// #define UNLIKELY(x) (x) [[unlikely]]
// #else
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)


// C++ 20 Standardized as:
// [[likely]] [[unlikely]]

// inline auto ASSERT(bool cond, const std::string& msg) noexcept {
//   if ((!cond) [[unlikely]]){
//     std::cerr << "ASSERT :" << msg << std::endl;

//     exit(EXIT_FAILURE);
//   }
// }

// inline auto FATAL(const std::string& msg) noexcept {
//   std::cerr << "FATAL :" << msg << std::endl;

//   exit(EXIT_FAILURE);
// }

inline auto ASSERT(bool cond, const std::string& msg) noexcept {
  if (UNLIKELY(!cond)) {
    std::cerr << "ASSERT :" << msg << std::endl;

    exit(EXIT_FAILURE);
  }
}

inline auto FATAL(const std::string& msg) noexcept {
  std::cerr << "FATAL :" << msg << std::endl;

  exit(EXIT_FAILURE);
}

// #endif
