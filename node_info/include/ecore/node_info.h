#pragma once

#include "ecore/core.h"

#include <cstdint>
#include <iosfwd>
#include <vector>

namespace ecore::node_info {

enum class transport_protocol : uint8_t {
    udp,
    tcp,
};

enum class address_family : uint8_t {
    ipv4,
    ipv6,
};

struct node_info {
    transport_protocol protocol;
    address_family family;
    std::vector<uint8_t> ip;
    uint16_t port;
    core::public_key public_key;
};

// Takes a bytestream containing a node in the packed_node format and parses it
// into a reasonable struct.
node_info from_bytes(std::istream &bytestream);

}
