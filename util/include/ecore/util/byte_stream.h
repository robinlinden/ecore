#ifndef ECORE_UTIL_BYTE_STREAM_H
#define ECORE_UTIL_BYTE_STREAM_H

#include "ecore/util/serialize.h"

#include <istream>
#include <ostream>

namespace ecore::util {

class ByteOstream {
public:
    explicit ByteOstream(std::ostream &bytes) : bytes_{bytes} {}

    template <typename T>
    ByteOstream &operator<<(T v) {
        v = net_pack(v);
        bytes_.write(reinterpret_cast<const char *>(&v), sizeof(v));
        return *this;
    }

    template <typename T>
    ByteOstream &write(const T *v, std::streamsize s) {
        bytes_.write(reinterpret_cast<const char *>(v), s);
        return *this;
    }

private:
    std::ostream &bytes_;
};


class ByteIstream {
public:
    explicit ByteIstream(std::istream &bytes) : bytes_{bytes} {}

    template <typename T>
    ByteIstream &operator>>(T& v) {
        bytes_.read(reinterpret_cast<char *>(&v), sizeof(v));
        v = net_unpack(v);
        return *this;
    }

    template <typename T>
    ByteIstream &read(T *v, std::streamsize s) {
        bytes_.read(reinterpret_cast<char *>(v), s);
        return *this;
    }

private:
    std::istream &bytes_;
};

} // namespace ecore::util

#endif
