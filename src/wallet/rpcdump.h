// Copyright (c) 2017 The Lyokocoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LYOKOCOIN_WALLET_RPCDUMP_H
#define LYOKOCOIN_WALLET_RPCDUMP_H

#include <univalue.h>

class Config;
class CRPCTable;
class JSONRPCRequest;

void RegisterDumpRPCCommands(CRPCTable &t);

UniValue importmulti(const Config &config, const JSONRPCRequest &request);
UniValue dumpwallet(const Config &config, const JSONRPCRequest &request);
UniValue importwallet(const Config &config, const JSONRPCRequest &request);

#endif // LYOKOCOIN_WALLET_RPCDUMP_H
