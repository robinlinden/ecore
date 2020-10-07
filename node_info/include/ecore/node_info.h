#ifndef ECORE_NODE_INFO_H
#define ECORE_NODE_INFO_H

#include "ecore/core.h"

#include <cstdint>
#include <iosfwd>
#include <vector>

namespace ecore::node_info {

enum class TransportProtocol : uint8_t {
    Udp,
    Tcp,
};

enum class AddressFamily : uint8_t {
    IPv4,
    IPv6,
};

struct NodeInfo {
    TransportProtocol protocol;
    AddressFamily family;
    std::vector<uint8_t> ip;
    uint16_t port;
    core::PublicKey public_key;
};

// Takes a bytestream containing a node in the packed_node format and parses it
// into a reasonable struct.
NodeInfo from_bytes(std::istream &bytestream);

}

#endif
