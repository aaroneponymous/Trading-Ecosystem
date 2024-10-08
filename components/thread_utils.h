#pragma once

#include <iostream>
#include <atomic>
#include <thread>
#include <unistd.h> // Standard Symbolic Constants and Types Header File
#include <sys/syscall.h>


namespace Components {
    // set affinity for current thread to be ponned to the provided core_id.
    inline auto setThreadCore(int core_id) noexcept {
        cpu_set_t cpuset;

        CPU_ZERO(&cpuset);
        CPU_SET(core_id, &cpuset);

        return (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) == 0);
    }


    //// Creates a thread instance, sets affinity on it, assigns it a name and
    //// pasess the function to be run on that thread as well as the arguments to the function
    template<typename T, typename... A>
    inline auto createAndStartThread(int core_id, const std::string& name, T &&func, A &&... args) noexcept {
        
        auto t = new std::thread([&]() {
            if (core_id >= 0 && !setThreadCore(core_id)) {
                std::cerr << "Failed to set core affinity for " << name << " " << pthread_self() << " to " << core_id << std::endl;
                exit(EXIT_FAILURE);
            }
            
            std::cerr << "Set core affinity for " << name << " " << pthread_self() << " to " << core_id << std::endl;

            std::forward<T>(func)((std::forward<A>(args))...);
        });

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1s);
        
        return t;
    }

}
