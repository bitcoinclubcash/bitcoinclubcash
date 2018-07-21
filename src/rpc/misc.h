// Copyright (c) 2017 The Lyokocoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LYOKOCOIN_RPCMISC_H
#define LYOKOCOIN_RPCMISC_H

#include "script/script.h"

class CWallet;
class UniValue;

CScript createmultisig_redeemScript(CWallet *const pwallet,
                                    const UniValue &params);

#endif // LYOKOCOIN_RPCBLOCKCHAIN_H
