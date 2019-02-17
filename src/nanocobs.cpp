#include "../include/nanocobs.h"
#include <cstring>

void write_packet(size_t len, unsigned char *dst, const unsigned char *src);

size_t cobs::encode(const unsigned char *src, const size_t len, unsigned char *dst) {
    int src_ptr = 0;
    int dst_ptr = 0;
    for (int i = 0; i < len; i++) {
        if ((i - src_ptr) > 0 && (i - src_ptr) % 254 == 0) {
            write_packet(254, &dst[dst_ptr], &src[src_ptr]);
            dst_ptr += 255;
            src_ptr += 254;
        } else if (src[i] == 0x00) {
            auto l = (size_t) (i - src_ptr);
            write_packet(l, &dst[dst_ptr], &src[src_ptr]);
            dst_ptr += l + 1;
            src_ptr = i + 1;
        }
    }
    write_packet(len - src_ptr, &dst[dst_ptr], &src[src_ptr]);
    dst_ptr += len - src_ptr + 1;
    dst[dst_ptr] = 0x00;

    return (size_t) dst_ptr + 1;
}

size_t cobs::decode(const unsigned char *src, const size_t len, unsigned char *dst) {
    size_t src_ptr = 0;
    size_t dst_ptr = 0;
    while (src_ptr < len - 1) {
        if (src[src_ptr] == 0xff) {
            memcpy(&dst[dst_ptr], &src[src_ptr + 1], 254);
            src_ptr += 255;
            dst_ptr += 254;
        } else {
            size_t l = (size_t) src[src_ptr] - 1;
            memcpy(&dst[dst_ptr], &src[src_ptr + 1], l);
            dst[dst_ptr + l] = 0x00;
            dst_ptr += l + 1;
            src_ptr += l + 1;
        }
    }

    return dst_ptr;
}

size_t cobs::encode_upper_bound(size_t i) {
    return i + (i / 254) + 2;
}

void write_packet(const size_t len, unsigned char *dst, const unsigned char *src) {
    dst[0] = (char) (len + 1);
    memcpy(&dst[1], src, len);
}

