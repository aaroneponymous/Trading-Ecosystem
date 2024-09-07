#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <fcntl.h>

#include "macros.h"
#include "logging.h"

namespace Components {


    // Max number of pending / unaccepted TCP connections
    constexpr int MaxTCPServerBacklog = 1024;

    // Convert interface name "eth0" to ip "123.123.123.123"
    inline auto getIfaceIP(const std::string &iface) -> std::string {
        char buf[NI_MAXHOST] = {'\0'};
        ifaddrs *ifaddr = nullptr;

        if(getifaddrs(&ifaddr) != -1) {
            for (ifaddrs *ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
                if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET && iface == ifa->ifa_name) {
                    getnameinfo(ifa->ifa_addr, sizeof(sockaddr_in), buf, sizeof(buf), NULL, 0, NI_NUMERICHOST); // Converts right here with the NI_NUMERICHOST Flag
                    break;
                }
            }

            freeifaddrs(ifaddr);
        }

        return buf;
    }

    // Sockets will not block on read - Return immediately if data unavailable
    inline auto setNonBlocking(int fd) -> bool {
        const auto flags = fcntl(fd, F_GETFL, 0);
        if (flags & O_NONBLOCK)
            return true;
        return (fcntl(fd, F_SETFL, flags | O_NONBLOCK) != -1);
    }

    // Disable Nagle's Algorithm and associated delays
    







   

    auto setNoDelay(int fd) -> bool;
    auto setSOTimeStamp(int fd) -> bool;
    auto wouldBlock() -> bool;
    auto setMcastTTL(int fd, int ttl) -> bool;
    auto setTTL(int fd, int ttl) -> bool;
    auto join(int fd, const std::string &ip, const std::string &iface, int port) -> bool;


}