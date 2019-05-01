#include "ecore/state_format.h"

#include <cstdint>
#include <string>
#include <vector>

namespace ecore::state_format {
namespace {

struct state_format_header {
    uint32_t zeroes{0};
    const uint32_t cookie{0x15ED1B1F};
    // List of sections.
};

struct section_header {
    uint32_t length;
    uint16_t type;
    const uint16_t cookie{0x01CE};
    // Section.
};

enum class section_type {
    nospam_keys = 0x01,
    dht = 0x02,
    friends = 0x03,
    name = 0x04,
    status_message = 0x05,
    status = 0x06,
    tcp_relays = 0x0A,
    path_nodes = 0x0B,
    conferences = 0x14,
    eof = 0xFF,
};

// nospam_keys
struct nospam_and_keys {
    uint32_t nospam;
    uint8_t public_key[32];
    uint8_t secret_key[32];
};

// dht
struct dht {
    const uint32_t cookie{0x159000D};
    // List of DHT sections.
};

struct dht_section_header {
    uint32_t length;
    uint16_t type;
    const uint16_t cookie{0x11CE};
    // DHT section.
};

enum class dht_section_type {
    nodes = 0x04,
};

struct dht_nodes {
    // List of DHT nodes. TODO: std::vector<node_info>
};

// friends
using friends = std::vector<contact>;

enum class friend_status : uint8_t {
    not_a_friend = 0,
    friend_added = 1,
    friend_request_sent = 2,
    confirmed_friend = 3,
    friend_online = 4,
};

// Not called friend due to a conflict with the C++ keyword.
struct contact {
    friend_status status;
    uint8_t public_key[32];
    uint8_t friend_request_message[1024];
    // 1 byte padding
    uint16_t friend_request_message_size;
    uint8_t name[128];
    uint16_t name_size;
    uint8_t status_message[1007];
    // 1 byte padding
    uint16_t status_message_size;
    uint8_t user_status;
    // 3 byte padding
    uint32_t nospam;
    uint64_t last_seen_time;
};

// name
struct name {
    std::string name;
};

// status_message
struct status_message {
    std::string status_message;
};

// status
struct status {
    uint8_t status;
};

// tcp_relays
struct tcp_relays {
    // List of TCP relays. TODO: std::vector<node_info>
};

// path_nodes
struct path_nodes {
    // List of path nodes. TODO: std::vector<node_info>
};

// conferences
struct conferences {
    std::vector<conference>
};

struct conference {
    uint8_t type;
    uint32_t id;
    uint32_t message_number;
    uint16_t lossy_message_number;
    uint16_t peer_number;
    uint32_t number_of_peers;
    uint8_t title_size;
    std::string title;
    std::vector<peer>
};

struct peer {
    uint8_t public_key[32];
    uint8_t dht_public_key[32];
    uint16_t peer_number;
    uint64_t last_active_timestamp;
    uint8_t name_size;
    std::string name;
};

// eof
struct eof {};

} // namespace

} // ecore::state_format
