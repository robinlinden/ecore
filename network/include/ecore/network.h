#pragma once

#include <cstdint>

namespace ecore::network {

enum class packet_kind : uint8_t {
    ping_request = 0x00,
    ping_response = 0x01,
    nodes_request = 0x02,
    nodes_response = 0x04,
    cookie_request = 0x18,
    cookie_response = 0x19,
    crypto_handshake = 0x1a,
    crypto_data = 0x1b,
    dht_request = 0x20,
    lan_discovery = 0x21,
    onion_request_0 = 0x80,
    onion_request_1 = 0x81,
    onion_request_2 = 0x82,
    announce_request = 0x83,
    announce_response = 0x84,
    onion_data_request = 0x85,
    onion_data_response = 0x86,
    onion_response_3 = 0x8c,
    onion_response_2 = 0x8d,
    onion_response_1 = 0x8e,
    bootstrap_info = 0xf0,
};

}
