#pragma once
#include <iostream>
#include <atomic>
#include <thread>
#include <unistd.h> // Standard Symbolic Constants and Types Header File
#include <sys/syscall.h>

template<typename T, typename... A>
inline auto createAndStartThread(int core_id, const std::string &name, T &&func, A &&... args) noexcept {
        std::atomic<bool> running(false), failed(false);

        // Thread Creation Lambda
        // In a lambda expression, the [&] is a capture clause that specifies how external variables should be captured. 
        // In this case, [&] means that all external variables referenced in the lambda should be captured by reference.
        auto thread_body = [&] {
            if (core_id >= 0 && !setThreadCore(core_id)) {
                std::cerr << "Failed to set core affinity for " << name << 
                    " " << pthread_self() << " to " << core_id << std::endl;
                failed = true;
                return;
            }

            std::cout << "Set core affinity for " << name << " " <<
                pthread_self() << " to " << core_id << std::endl;
            running = true;
            std::forward<T>(func)((std::forward<A>(args))...);
        };

        auto t = new std::thread(thread_body);
        while (!running && !failed) {
            using namespace std::literals::chrono_literals;
            std::this_thread::sleep_for(1s);
        }
        if (failed) {
            t->join();
            delete t;
            t = nullptr;
        }

        return t;
    }

inline auto setThreadCore(int core_id) noexcept {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    // pthread_setaffinity_np on success returns 0
    // on error, they return a non-zero error number
    return (pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset) == 0);
}