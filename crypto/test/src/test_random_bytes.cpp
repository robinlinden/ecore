#include "ecore/crypto.h"

#include <catch2/catch.hpp>

using namespace ecore::crypto;

namespace {

TEST_CASE("Random bytes are probably random") {
    REQUIRE(random_bytes() != random_bytes());
}

}
