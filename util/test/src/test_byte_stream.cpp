#include "ecore/util/byte_stream.h"

#include <catch2/catch.hpp>

#include <cstring>
#include <sstream>

using namespace ecore;

namespace {

TEST_CASE("{i,o}stream") {
    SECTION("stream operators") {
        std::stringstream ss;
        util::ByteOstream ostream{ss};

        ostream << 1 << 2 << 3;

        const auto str = ss.str();
        REQUIRE(str.size() == sizeof(int) * 3);
        const int expected[] = {util::net_pack(1), util::net_pack(2), util::net_pack(3)};
        REQUIRE(std::memcmp(str.c_str(), expected, str.size()) == 0);

        util::ByteIstream istream{ss};
        int a, b, c;
        istream >> c >> b >> a;
        REQUIRE(a == 3);
        REQUIRE(b == 2);
        REQUIRE(c == 1);
    }

    SECTION("read/write") {
        const std::string_view hello{"hello world"};

        std::stringstream ss;
        util::ByteOstream ostream{ss};

        ostream << hello.size();
        ostream.write(hello.data(), hello.size());
        REQUIRE(ss.str().size() == sizeof(std::size_t) + hello.size());

        util::ByteIstream istream{ss};
        std::size_t len{};
        istream >> len;
        REQUIRE(len == hello.size());
        std::string text{};
        text.resize(len);
        istream.read(text.data(), len);
        REQUIRE(text == hello);
    }
}

} // namespace
