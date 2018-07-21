// Copyright (c) 2017 The Lyokocoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LYOKOCOIN_RPC_MINING_H
#define LYOKOCOIN_RPC_MINING_H

#include "script/script.h"

#include <univalue.h>

#include <memory>

class Config;

/** Generate blocks (mine) */
UniValue generateBlocks(const Config &config,
                        std::shared_ptr<CReserveScript> coinbaseScript,
                        int nGenerate, uint64_t nMaxTries, bool keepScript);

#endif
