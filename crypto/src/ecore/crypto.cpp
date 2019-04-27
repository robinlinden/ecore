#include "ecore/crypto.h"

#include <sodium.h>

namespace ecore::crypto {

uint32_t random_bytes() {
    return randombytes_random();
}

}
