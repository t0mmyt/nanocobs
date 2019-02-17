#include <iostream>
#include "../include/nanocobs.h"
#include "catch.hpp"

bool matches(const unsigned char a[], const unsigned char b[], size_t len);

void println(const unsigned char s[], size_t len);

TEST_CASE("Short sequences", "") {
    unsigned char src1[] = {0x00, 0x00};
    unsigned char dst1[] = {0x01, 0x01, 0x01, 0x00};
    unsigned char t_enc1[sizeof(dst1)];
    unsigned char t_dec1[sizeof(src1)];

    unsigned char src2[] = {0x11, 0x22, 0x00, 0x33};
    unsigned char dst2[] = {0x03, 0x11, 0x22, 0x02, 0x33, 0x00};
    unsigned char t_enc2[sizeof(dst2)];
    unsigned char t_dec2[sizeof(src2)];

    cobs::encode(src1, sizeof(src1), t_enc1);
    REQUIRE(matches(dst1, t_enc1, sizeof(dst1)));

    cobs::decode(dst1, sizeof(dst1), t_dec1);
    REQUIRE(matches(src1, t_dec1, sizeof(src1)));

    cobs::encode(src2, sizeof(src2), t_enc2);
    REQUIRE(matches(dst2, t_enc2, sizeof(dst2)));

    cobs::decode(dst2, sizeof(dst2), t_dec2);
    REQUIRE(matches(src2, t_dec2, sizeof(src2)));
}

// TODO Long sequence tests (need samples)

bool matches(const unsigned char a[], const unsigned char b[], const size_t len) {
    for (size_t i = 0; i < len; ++i) {
        if (a[i] != b[i]) {
            println(a, len);
            printf("%s", "\n");
            println(b, len);
            return false;
        }
    }
    return true;
}

void println(const unsigned char *s, size_t len) {
    for (int i = 0; i < len; i++) {
        if (i % 80 == 0) std::cout << std::endl;
        printf("%02x ", (s[i]));
    }
    std::cout << ", ";
}