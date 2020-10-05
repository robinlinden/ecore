#include "ecore/util/serialize.h"

#include <catch2/catch.hpp>

#include <cstdint>

using namespace ecore;

namespace {

TEST_CASE("serialize") {
    const auto repack = [](const auto v) { return util::net_unpack(util::net_pack(v)); };
    SECTION("u8") { REQUIRE(repack(static_cast<uint8_t>(143)) == 143); }
    SECTION("u16") { REQUIRE(repack(static_cast<uint16_t>(1213)) == 1213); }
    SECTION("u32") { REQUIRE(repack(static_cast<uint32_t>(19'920'210)) == 19'920'210); }
    SECTION("u64") { REQUIRE(repack(static_cast<uint64_t>(9'999'999'999)) == 9'999'999'999); }
    SECTION("i8") { REQUIRE(repack(static_cast<int8_t>(-99)) == -99); }
    SECTION("i16") { REQUIRE(repack(static_cast<int16_t>(-1213)) == -1213); }
    SECTION("i32") { REQUIRE(repack(static_cast<int32_t>(-19'920'210)) == -19'920'210); }
    SECTION("i64") { REQUIRE(repack(static_cast<int64_t>(-9'999'999'999)) == -9'999'999'999); }
}

} // namespace
