#include "ecore/node_info.h"

#include "ecore/core.h"

#include <catch2/catch.hpp>

#include <cassert>
#include <cstdlib>
#include <sstream>

using namespace ecore::node_info;
using ecore::core::PublicKey;

namespace {

enum TransportAndFamily : unsigned char {
    udp_ipv4 = 2,
    udp_ipv6 = 10,
    tcp_ipv4 = 130,
    tcp_ipv6 = 138,
};

// Length  Type                Contents
// 1 bit   Transport Protocol  UDP = 0, TCP = 1
// 7 bit   Address Family      2 = IPv4, 10 = IPv6
// 4 | 16  IP address          4 bytes for IPv4, 16 bytes for IPv6
// 2       Port Number         Port number
// 32      Public Key          Node ID
std::stringstream make_bytes(
        uint8_t transport_and_family,
        const std::vector<uint8_t>& ip,
        uint16_t port,
        PublicKey pk) {
    std::stringstream ss;

    ss.put(transport_and_family);

    for (const uint8_t i : ip) {
        ss.put(i);
    }

    ss.write(reinterpret_cast<const char *>(&port), 2);

    for (const uint8_t i : pk) {
        ss.put(i);
    }

    return ss;
}

PublicKey random_key() {
    PublicKey pk;
    for (size_t i = 0; i < pk.size(); ++i) {
        pk[i] = rand() & 0xFF;
    }
    return pk;
}

size_t streamsize(std::istream &stream) {
    stream.seekg(0, std::ios::end);
    std::istream::pos_type size = stream.tellg();
    stream.seekg(0, std::ios::beg);

    assert(size >= 0);
    assert(static_cast<uint64_t>(size) <= std::numeric_limits<size_t>::max());
    return static_cast<size_t>(size);
}

TEST_CASE("node_info: length of tested bytes") {
    const std::vector<uint8_t> ipv4{1, 10, 100, 255};
    const uint16_t port{52089};
    const auto key = random_key();

    auto bytes = make_bytes(tcp_ipv4, ipv4, port, key);
    REQUIRE(streamsize(bytes) == 39);

    std::vector<uint8_t> ipv6{
            1, 10, 100, 255,
            2, 20, 200, 66,
            1, 10, 100, 255,
            1, 10, 100, 255};
    bytes = make_bytes(tcp_ipv6, ipv6, port, key);
    REQUIRE(streamsize(bytes) == 51);
}

TEST_CASE("node_info: parse ipv4 tcp node") {
    const std::vector<uint8_t> ip{1, 10, 100, 255};
    const uint16_t port{8089};
    const auto key = random_key();

    auto bytes = make_bytes(tcp_ipv4, ip, port, key);
    NodeInfo info = from_bytes(bytes);

    REQUIRE(info.protocol == TransportProtocol::Tcp);
    REQUIRE(info.family == AddressFamily::IPv4);
    REQUIRE(info.ip == ip);
    REQUIRE(info.port == port);
    REQUIRE(info.public_key == key);
}

TEST_CASE("node_info: parse ipv6 udp node") {
    const std::vector<uint8_t> ip{
            1, 10, 100, 255,
            2, 20, 200, 66,
            1, 10, 100, 255,
            1, 10, 100, 255};
    const uint16_t port{25000};
    const auto key = random_key();

    auto bytes = make_bytes(udp_ipv6, ip, port, key);
    NodeInfo info = from_bytes(bytes);

    REQUIRE(info.protocol == TransportProtocol::Udp);
    REQUIRE(info.family == AddressFamily::IPv6);
    REQUIRE(info.ip == ip);
    REQUIRE(info.port == port);
    REQUIRE(info.public_key == key);
}

} // namespace
