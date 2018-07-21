// Copyright (c) 2014-2016 The Lyokocoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LYOKOCOIN_CRYPTO_SHA1_H
#define LYOKOCOIN_CRYPTO_SHA1_H

#include <cstdint>
#include <cstdlib>

/** A hasher class for SHA1. */
class CSHA1 {
private:
    uint32_t s[5];
    uint8_t buf[64];
    uint64_t bytes;

public:
    static const size_t OUTPUT_SIZE = 20;

    CSHA1();
    CSHA1 &Write(const uint8_t *data, size_t len);
    void Finalize(uint8_t hash[OUTPUT_SIZE]);
    CSHA1 &Reset();
};

#endif // LYOKOCOIN_CRYPTO_SHA1_H
