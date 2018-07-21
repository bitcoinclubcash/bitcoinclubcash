// Copyright (c) 2017 The Lyokocoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LYOKOCOIN_RPCBLOCKCHAIN_H
#define LYOKOCOIN_RPCBLOCKCHAIN_H

#include <univalue.h>

class CBlockIndex;
class Config;
class JSONRPCRequest;

UniValue getblockchaininfo(const Config &config, const JSONRPCRequest &request);

double GetDifficulty(const CBlockIndex *blockindex);

#endif // LYOKOCOIN_RPCBLOCKCHAIN_H
