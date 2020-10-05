#pragma once

#include <climits>
#include <cstddef>

namespace ecore::util {

template <typename T>
T net_pack(const T in) {
    T out{};
    auto *const bytes = reinterpret_cast<std::byte *>(&out);

    for (std::size_t i = 0; i < sizeof(T); ++i) {
        bytes[i] = static_cast<std::byte>(in >> ((sizeof(T) - i - 1) * CHAR_BIT));
    }

    return out;
}

template <typename T>
T net_unpack(const T in) {
    return net_pack(in);
}

} // namespace ecore::util
