#include "ecore/crypto.h"

#include <catch2/catch.hpp>

using namespace ecore::crypto;

namespace {

TEST_CASE("crypto: random bytes") {
    REQUIRE(random_bytes() != random_bytes());
}

}
