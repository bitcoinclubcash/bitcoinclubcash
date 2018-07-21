// Copyright (c) 2009-2016 The Lyokocoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LYOKOCOIN_CHECKPOINTS_H
#define LYOKOCOIN_CHECKPOINTS_H

#include "uint256.h"

#include <map>

class CBlockIndex;
struct CCheckpointData;

/**
 * Block-chain checkpoints are compiled-in sanity checks.
 * They are updated every release or three.
 */
namespace Checkpoints {

//! Returns true if block passes checkpoint checks
bool CheckBlock(const CCheckpointData &data, int nHeight, const uint256 &hash);

//! Returns last CBlockIndex* in mapBlockIndex that is a checkpoint
CBlockIndex *GetLastCheckpoint(const CCheckpointData &data);

} // namespace Checkpoints

#endif // LYOKOCOIN_CHECKPOINTS_H
