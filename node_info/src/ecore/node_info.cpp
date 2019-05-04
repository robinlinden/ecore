#include "ecore/node_info.h"

#include <istream>
#include <stdexcept>

namespace ecore::node_info {
namespace {

enum transport_and_family : unsigned char {
    udp_ipv4 = 2,
    udp_ipv6 = 10,
    tcp_ipv4 = 130,
    tcp_ipv6 = 138,
};

} // namespace

// Length  Type                Contents
// 1 bit   Transport Protocol  UDP = 0, TCP = 1
// 7 bit   Address Family      2 = IPv4, 10 = IPv6
// 4 | 16  IP address          4 bytes for IPv4, 16 bytes for IPv6
// 2       Port Number         Port number
// 32      Public Key          Node ID

node_info from_bytes(std::istream &bytestream) {
    node_info info;

    char transport_and_family;
    if (!bytestream.read(&transport_and_family, 1)) {
        throw std::runtime_error("family read");
    }

    switch (static_cast<unsigned char>(transport_and_family)) {
    case udp_ipv4:
        info.protocol = transport_protocol::udp;
        info.family = address_family::ipv4;
        break;
    case udp_ipv6:
        info.protocol = transport_protocol::udp;
        info.family = address_family::ipv6;
        break;
    case tcp_ipv4:
        info.protocol = transport_protocol::tcp;
        info.family = address_family::ipv4;
        break;
    case tcp_ipv6:
        info.protocol = transport_protocol::tcp;
        info.family = address_family::ipv6;
        break;
    default:
        throw std::runtime_error("family parsing");
    }

    info.ip.resize(info.family == address_family::ipv4 ? 4 : 16);
    if (!bytestream.read(
            reinterpret_cast<char *>(info.ip.data()),
            info.ip.size())) {
        throw std::runtime_error("ip read");
    }

    if (!bytestream.read(
            reinterpret_cast<char *>(&info.port),
            sizeof(info.port))) {
        throw std::runtime_error("port read");
    }

    if (!bytestream.read(
            reinterpret_cast<char *>(info.public_key.data()),
            info.public_key.size())) {
        throw std::runtime_error("pk read");
    }

    return info;
}

}
