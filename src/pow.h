// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Lyokocoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LYOKOCOIN_POW_H
#define LYOKOCOIN_POW_H

#include <cstdint>

class CBlockHeader;
class CBlockIndex;
class Config;
class uint256;

uint32_t GetNextWorkRequired(const CBlockIndex *pindexPrev,
                             const CBlockHeader *pblock, const Config &config);
uint32_t CalculateNextWorkRequired(const CBlockIndex *pindexPrev,
                                   int64_t nFirstBlockTime,
                                   const Config &config);

/**
 * Check whether a block hash satisfies the proof-of-work requirement specified
 * by nBits
 */
bool CheckProofOfWork(uint256 hash, uint32_t nBits, const Config &config);

/**
 * Lyokocoin cash's difficulty adjustment mechanism.
 */
uint32_t GetNextCashWorkRequired(const CBlockIndex *pindexPrev,
                                 const CBlockHeader *pblock,
                                 const Config &config);

#endif // LYOKOCOIN_POW_H
