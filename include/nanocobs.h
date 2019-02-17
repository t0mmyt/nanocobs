#ifndef NANOCOBS_LIBRARY_H
#define NANOCOBS_LIBRARY_H

#include <string.h>

namespace cobs {
    size_t encode(const unsigned char *src, size_t len, unsigned char dst[]);

    size_t decode(const unsigned char *src, size_t len, unsigned char dst[]);

    size_t encode_upper_bound(size_t i);
}
#endif