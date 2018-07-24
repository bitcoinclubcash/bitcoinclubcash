// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Lyokocoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include "config/lyokocoin-config.h"
#endif

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include "arith_uint256.h"

#include <cassert>

#include "chainparamsseeds.h"

static const uint64_t BUFFER_SIZE = 1000 * 1000;

static CBlock CreateGenesisBlock(const char *pszTimestamp,
                                 const CScript &genesisOutputScript,
                                 uint32_t nTime, uint32_t nNonce,
                                 uint32_t nBits, int32_t nVersion,
                                 const Amount genesisReward) {
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig =
        CScript() << 486604799 << CScriptNum(4)
                  << std::vector<uint8_t>((const uint8_t *)pszTimestamp,
                                          (const uint8_t *)pszTimestamp +
                                              strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime = nTime;
    genesis.nBits = nBits;
    genesis.nNonce = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation transaction
 * cannot be spent since it did not originally exist in the database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000,
 * hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893,
 * vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase
 * 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce,
                                 uint32_t nBits, int32_t nVersion,
                                 const Amount genesisReward) {
    const char *pszTimestamp =
        "The Times 03/Jan/2018 Bitcoin is name of the game for new generation of firms";
    const CScript genesisOutputScript =
        CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909"
                              "a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112"
                              "de5c384df7ba0b8d578a4c702b6bf11d5f")
                  << OP_CHECKSIG;
    // std::cout << "Genesis Output Script" << genesisOutputScript.GetHex() << "\n";
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce,
                              nBits, nVersion, genesisReward);
}

void CChainParams::UpdateBIP9Parameters(Consensus::DeploymentPos d,
                                        int64_t nStartTime, int64_t nTimeout) {
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP34Height = 227931;
        consensus.BIP34Hash = uint256S(
            "000000000000024b89b42a942fe0d9fea3bb44ab7bd1b19115dd6a759c0808b8");
        // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.BIP65Height = 388381;
        // 00000000000000000379eaa19dce8c9b722d46ae6a57c2f1a988119488b50931
        consensus.BIP66Height = 363725;
        consensus.powLimit = uint256S(
            "00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // 1 day
        consensus.nPowTargetTimespan = 1 * 24 * 60 * 60;
        consensus.nPowTargetSpacing = 5 * 60;   // 5 mins
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        // 90% of 288
        consensus.nRuleChangeActivationThreshold = 260;
        // nPowTargetTimespan / nPowTargetSpacing
        consensus.nMinerConfirmationWindow = 288;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime =
            1199145601;
        // December 31, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout =
            1230767999;

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        // May 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime =
            1462060800;
        // May 1st, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1493596800;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S(
            "000000000000000000000000000000000000000000a0f3064330647e2f6c4828");
        // 000000000000000000000000000000000000000000a0f3064330647e2f6c4828
        // By default assume that the signatures in ancestors of this block are
        // valid.
        consensus.defaultAssumeValid = uint256S(
            "000000000000000000e45ad2fbcc5ff3e85f0868dd8f00ad4e92dffabe28f8d2");

        // August 1, 2017 hard fork
        consensus.uahfHeight = 478558;

        // November 13, 2017 hard fork
        consensus.daaHeight = 504031;

        // May 15, 2018 hard fork
        consensus.monolithActivationTime = 1526400000;

        // Nov 15, 2018 hard fork
        consensus.magneticAnomalyActivationTime = 1542300000;

        /**
         * The message start string is designed to be unlikely to occur in
         * normal data. The characters are rarely used upper ASCII, not valid as
         * UTF-8, and produce a large 32-bit integer with any alignment.
         */
        diskMagic[0] = 0xf9;
        diskMagic[1] = 0xbe;
        diskMagic[2] = 0xb4;
        diskMagic[3] = 0xd9;
        netMagic[0] = 0xe3;
        netMagic[1] = 0xe1;
        netMagic[2] = 0xf3;
        netMagic[3] = 0xe8;
        nDefaultPort = 5333;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1532687395, 0, 0x1d00ffff, 1,
                                     30 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        std::cout << std::string("Mainnet Network...\n");
        //  calculate Genesis Block
        //  Reset genesis
        consensus.hashGenesisBlock = uint256S("0x");
        std::cout << std::string("Begin calculating Mainnet Genesis Block:\n");
        if (true && (genesis.GetHash() != consensus.hashGenesisBlock)) {
            LogPrintf("Calculating Mainnet Genesis Block:\n");
            arith_uint256 hashTarget = arith_uint256().SetCompact(genesis.nBits);
            uint256 hash;
            genesis.nNonce = 0;
            // This will figure out a valid hash and Nonce if you're
            // creating a different genesis block:
            // uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            // hashTarget.SetCompact(genesis.nBits, &fNegative, &fOverflow).getuint256();
            // while (genesis.GetHash() > hashTarget)
            while (UintToArith256(genesis.GetHash()) > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    LogPrintf("NONCE WRAPPED, incrementing time");
                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                    ++genesis.nTime;
                }
                if (genesis.nNonce % 10000 == 0)
                {
                    LogPrintf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                    // std::cout << strNetworkID << " nonce: " << genesis.nNonce << " time: " << genesis.nTime << " hash: " << genesis.GetHash().ToString().c_str() << "\n";
                }
            }
            std::cout << "Mainnet ---\n";
            std::cout << "  nonce: " << genesis.nNonce <<  "\n";
            std::cout << "   time: " << genesis.nTime << "\n";
            std::cout << "   hash: " << genesis.GetHash().ToString().c_str() << "\n";
            std::cout << "   merklehash: "  << genesis.hashMerkleRoot.ToString().c_str() << "\n";
            // Mainnet --- nonce: 296277 time: 1390095618 hash: 000000bdd771b14e5a031806292305e563956ce2584278de414d9965f6ab54b0
        }
        std::cout << std::string("Finished calculating Mainnet Genesis Block:\n");


        assert(genesis.hashMerkleRoot ==
               uint256S("0xf149d7ec44780c732ef8ddb485e56b0a7b3dbc982c8ed8fcf1fec033f7a795be"));
        assert(consensus.hashGenesisBlock ==
               uint256S("0x00000000b99bc0242d6ccd67a0727301d7eb92bd38677f7350034b6c690045dd"));

        // Note that of those with the service bits flag, most only support a
        // subset of possible options.
        // Lyokocoin ABC seeder
        // vSeeds.push_back(CDNSSeedData("vps1", "172.31.25.26", true));
        // vSeeds.push_back(CDNSSeedData("lapurema", "14.175.128.184", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<uint8_t>(1, 0);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<uint8_t>(1, 5);
        base58Prefixes[SECRET_KEY] = std::vector<uint8_t>(1, 128);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};
        cashaddrPrefix = "lyokocoincash";

        // vFixedSeeds = std::vector<SeedSpec6>(
        //     pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        vFixedSeeds = std::vector<SeedSpec6>();

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            .mapCheckpoints = {
                {0, uint256S("0x00000000b99bc0242d6ccd67a0727301d7eb92bd38677f7350034b6c690045dd")},
            }};

        // Data as of block
        // 000000000000000001d2ce557406b017a928be25ee98906397d339c3f68eec5d
        // (height 523992).
        chainTxData = ChainTxData{
            // UNIX timestamp of last known number of transactions.
            1532154995,
            // Total number of transactions between genesis and that timestamp
            // (the tx=... number in the SetBestChain debug.log lines)
            248589038,
            // Estimated number of transactions per second after that timestamp.
            1.0
        };
    }
};


/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP34Height = 21111;
        consensus.BIP34Hash = uint256S(
            "0000000023b3a96d3484e5abb3755c413e7d41500f8e2a5c3f0dd01299cd8ef8");
        // 00000000007f6655f22f98e72ed80d8b06dc761d5da09df0fa1dc4be4f861eb6
        consensus.BIP65Height = 581885;
        // 000000002104c8c45e99a8853285a3b592602a3ccde2b832481da85e9e4ba182
        consensus.BIP66Height = 330776;
        consensus.powLimit = uint256S(
            "00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // 1 day
        consensus.nPowTargetTimespan = 1 * 24 * 60 * 60;
        consensus.nPowTargetSpacing = 5 * 60;   // 5 mins
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        // 75% for testchains
        consensus.nRuleChangeActivationThreshold = 216;
        // nPowTargetTimespan / nPowTargetSpacing
        consensus.nMinerConfirmationWindow = 288;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        // December 31, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
            // 1230767999;

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        // March 1st, 2016
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1456790400;
        // May 1st, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        // 1493596800;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S(
            "00000000000000000000000000000000000000000000002a650f6ff7649485da");

        // By default assume that the signatures in ancestors of this block are
        // valid.
        consensus.defaultAssumeValid = uint256S(
            "0000000000327972b8470c11755adf8f4319796bafae01f5a6650490b98a17db");

        // August 1, 2017 hard fork
        consensus.uahfHeight = 1155875;
        // 1155875;

        // November 13, 2017 hard fork
        consensus.daaHeight = 1188697;
        // 1188697;

        // May 15, 2018 hard fork
        consensus.monolithActivationTime = 1526400000;

        // Nov 15, 2018 hard fork
        consensus.magneticAnomalyActivationTime = 1542300000;

        diskMagic[0] = 0x0b;
        diskMagic[1] = 0x11;
        diskMagic[2] = 0x09;
        diskMagic[3] = 0x07;
        netMagic[0] = 0xf4;
        netMagic[1] = 0xe5;
        netMagic[2] = 0xf3;
        netMagic[3] = 0xf4;
        nDefaultPort = 15333;
        nPruneAfterHeight = 1000;

        genesis =
            CreateGenesisBlock(1532687395, 1989679220, 0x1d00ffff, 1, 30 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        std::cout << "test net... \n";
        std::cout << "hash genesis block: " << consensus.hashGenesisBlock.GetHex() << "\n";
        std::cout << "hash merkle root: " << genesis.hashMerkleRoot.GetHex() << "\n";

/**
        // calculate Genesis Block
        // Reset genesis
        consensus.hashGenesisBlock = uint256S("0x");
        std::cout << std::string("Begin calculating Testnet Genesis Block:\n");
        if (true && (genesis.GetHash() != consensus.hashGenesisBlock)) {
            LogPrintf("Calculating Mainnet Genesis Block:\n");
            arith_uint256 hashTarget = arith_uint256().SetCompact(genesis.nBits);
            uint256 hash;
            genesis.nNonce = 0;
            // This will figure out a valid hash and Nonce if you're
            // creating a different genesis block:
            // uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            // hashTarget.SetCompact(genesis.nBits, &fNegative, &fOverflow).getuint256();
            // while (genesis.GetHash() > hashTarget)
            while (UintToArith256(genesis.GetHash()) > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    LogPrintf("NONCE WRAPPED, incrementing time");
                    std::cout << std::string("NONCE WRAPPED, incrementing time:\n");
                    ++genesis.nTime;
                }
                if (genesis.nNonce % 10000 == 0)
                {
                    LogPrintf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                    // std::cout << strNetworkID << " nonce: " << genesis.nNonce << " time: " << genesis.nTime << " hash: " << genesis.GetHash().ToString().c_str() << "\n";
                }
            }
            std::cout << "Testnet ---\n";
            std::cout << "  nonce: " << genesis.nNonce <<  "\n";
            std::cout << "   time: " << genesis.nTime << "\n";
            std::cout << "   hash: " << genesis.GetHash().ToString().c_str() << "\n";
            std::cout << "   merklehash: "  << genesis.hashMerkleRoot.ToString().c_str() << "\n";
            // Testnet --- nonce: 296277 time: 1390095618 hash: 000000bdd771b14e5a031806292305e563956ce2584278de414d9965f6ab54b0
        }
        std::cout << std::string("Finished calculating Testnet Genesis Block:\n");

*/

        //
        // Search
        //
        // arith_uint256 hashTarget = arith_uint256().SetCompact(genesis.nBits);
        // arith_uint256 hashTarget = UintToArith256(genesis.GetHash());
        // std::cout << "hash target = " << hashTarget.GetHex() << "\n";
        // uint256 hash;
        // uint32_t nNonce = 0;
        // while (true) {
        //     if (ScanHash(&genesis, nNonce, &hash)) {
        //         if (UintToArith256(hash) <= hashTarget)
        //         {
        //             // Found a solution
        //             std::cout << "found count = " << nNonce << "\n";
        //             genesis.nNonce = nNonce;
        //             // assert(hash == genesis.GetHash());
        //             printf("BitcoinMiner:\n");
        //             printf("proof-of-work found  \n  hash: %u  \ntarget: %u\n", hash.GetHex(), hashTarget.GetHex());

        //             // In regression test mode, stop mining after a block is found.

        //             break;
        //         }
        //     }
        // }

        // std::cout << "block.nTime = " << genesis.nTime << "\n";
        // std::cout << "block.nNonce = " << genesis.nNonce << "\n";
        // std::cout << "block.GetHash = " << genesis.GetHash().GetHex() << "\n";


        // if (true && genesis.GetHash() != uint256S("0x")) {
        //     std::cout << "test net... \n" ;
        //     // const Config &config = GetConfig();
        //     // GlobalConfig config;

        //     bool fNegative;
        //     bool fOverflow;
        //     arith_uint256 bnTarget;

        //     // bnTarget.SetCompact(genesis.nBits, &fNegative, &fOverflow);
        //     arith_uint256 hashTarget = arith_uint256().SetCompact(genesis.nBits);
        //     std::cout << "hash target = " << hashTarget.GetHex() << "\n";

        //     while (true) {
        //         std::cout << "hash target = " << hashTarget.GetHex() << "\n";
        //         std::cout << "hash block = " << genesis.GetHash().GetHex() << "\n";

        //         // Check proof of work matches claimed amount
        //         if (UintToArith256(genesis.GetHash()) <= hashTarget) {
        //             break;
        //         }

        //         if ((genesis.nNonce & 0xFFF) == 0) {
        //             printf("nonce %08X: hash = %s \n", genesis.nNonce, genesis.ToString().c_str());
        //         }
        //         ++genesis.nNonce;
        //         if (genesis.nNonce == 0)
        //         {
        //             printf("NONCE WRAPPED, incrementing time\n");
        //             ++genesis.nTime;
        //         }
        //     }
        //     std::cout << "block.nTime = " << genesis.nTime << "\n";
        //     std::cout << "block.nNonce = " << genesis.nNonce << "\n";
        //     std::cout << "block.GetHash = " << genesis.GetHash().GetHex() << "\n";
        // }
        assert(genesis.hashMerkleRoot ==
               uint256S("0xa2873aabfba192ba62246155b9d6ee364c6cd7fa6767f5a2bb0e44388f06730d"));
        assert(consensus.hashGenesisBlock ==
               uint256S("0x000000001a1e6b91c15511587192c869db9fdff011a0a14f0e0db0aa03ef1317"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        // Bitcoin ABC seeder
        vSeeds.push_back(CDNSSeedData("", "", false));
        // vSeeds.push_back(CDNSSeedData("local", "", false));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<uint8_t>(1, 95);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<uint8_t>(1, 196);
        base58Prefixes[SECRET_KEY] = std::vector<uint8_t>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};
        cashaddrPrefix = "loctest";
        // vFixedSeeds = std::vector<SeedSpec6>(
        //     pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        vFixedSeeds = std::vector<SeedSpec6>();

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = {
            .mapCheckpoints = {
                {0, uint256S("0x000000001a1e6b91c15511587192c869db9fdff011a0a14f0e0db0aa03ef1317")},
            }};

        // Data as of block
        // 000000000005b07ecf85563034d13efd81c1a29e47e22b20f4fc6919d5b09cd6
        // (height 1223263)
        chainTxData = ChainTxData{
            1532687395,
            0,
            1.0
        };
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        // BIP34 has not activated on regtest (far in the future so block v1 are
        // not rejected in tests)
        consensus.BIP34Height = 100000000;
        consensus.BIP34Hash = uint256();
        // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP65Height = 1351;
        // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251;
        consensus.powLimit = uint256S(
            "7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // 1 day
        consensus.nPowTargetTimespan = 1 * 24 * 60 * 60;
        consensus.nPowTargetSpacing = 5 * 60;   // 5 mins
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        // 75% for testchains
        consensus.nRuleChangeActivationThreshold = 216;
        // Faster than normal for regtest (144 instead of 2016)
        consensus.nMinerConfirmationWindow = 288;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout =
            999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout =
            999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are
        // valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        // UAHF is always enabled on regtest.
        consensus.uahfHeight = 0;

        // November 13, 2017 hard fork is always on on regtest.
        consensus.daaHeight = 0;

        // May 15, 2018 hard fork.
        consensus.monolithActivationTime = 1526400000;

        // Nov 15, 2018 hard fork
        consensus.magneticAnomalyActivationTime = 1542300000;

        diskMagic[0] = 0xfa;
        diskMagic[1] = 0xbf;
        diskMagic[2] = 0xb5;
        diskMagic[3] = 0xda;
        netMagic[0] = 0xda;
        netMagic[1] = 0xb5;
        netMagic[2] = 0xbf;
        netMagic[3] = 0xfa;
        nDefaultPort = 18444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1296688602, 4, 0x207fffff, 1, 30 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock ==
               uint256S("0x6ad69e558f1834eb50a830ebc4ec3f0e09965a6babf9ac401580f446ab0c61a5"));
        assert(genesis.hashMerkleRoot ==
               uint256S("0xf149d7ec44780c732ef8ddb485e56b0a7b3dbc982c8ed8fcf1fec033f7a795be"));

        //!< Regtest mode doesn't have any fixed seeds.
        vFixedSeeds.clear();
        //!< Regtest mode doesn't have any DNS seeds.
        vSeeds.clear();

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = {.mapCheckpoints = {
                              {0, uint256S("0f9188f13cb7b2c71f2a335e3a4fc328bf5"
                                           "beb436012afca590b1a11466e2206")},
                          }};

        chainTxData = ChainTxData{0, 0, 0};

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<uint8_t>(1, 111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<uint8_t>(1, 196);
        base58Prefixes[SECRET_KEY] = std::vector<uint8_t>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};
        cashaddrPrefix = "bchreg";
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string &chain) {
    if (chain == CBaseChainParams::MAIN) {
        return std::unique_ptr<CChainParams>(new CMainParams());
    }

    if (chain == CBaseChainParams::TESTNET) {
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    }

    if (chain == CBaseChainParams::REGTEST) {
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    }

    throw std::runtime_error(
        strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string &network) {
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime,
                          int64_t nTimeout) {
    globalChainParams->UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
