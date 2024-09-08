#pragma once

#include <iostream>
#include <string>
#include <sstream>
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

  struct SocketCfg {
    std::string ip_;
    std::string iface_;
    int port_ = -1;
    bool is_udp_ = false;
    bool is_listening_ = false;
    bool needs_SO_timestamp_ = false;

    auto toString() const {
      std::stringstream ss;
      ss << "SocketCfg[ip:" << ip_
      << " iface:" << iface_
      << " port:" << port_
      << " is_dup" << is_udp_
      << " is_listening" << is_listening_
      << " needs_SO_timestamp" << needs_SO_timestamp_
      << " ]";

      return ss.str();
    }
  };


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
    inline auto disableNagle(int fd) -> bool {
      int one = 1;
      return (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<void *>(&one), sizeof(one)) != -1);
    } 

    // Allow software to receive timestamps on incoming packets
    inline auto setSOTimestamp(int fd) -> bool {
      int one = 1;
      return (setsockopt(fd, SOL_SOCKET, SO_TIMESTAMP, reinterpret_cast<void *>(&one), sizeof(one) != -1));
    }

    auto wouldBlock() -> bool {
      return (errno == EWOULDBLOCK || errno == EINPROGRESS);
    }

    // Time-To-Live (TTL) is a network level setting
    // Controls the maximum number of hops that a packet can take from sender to receiver
    inline auto setTTL(int fd, int ttl) -> bool {
      return (setsockopt(fd, IPPROTO_IP, IP_TTL, reinterpret_cast<void*>(&ttl), sizeof(ttl)) != -1);
    }


    auto join(int fd, const std::string &ip, const std::string &iface, int port) -> bool;


}