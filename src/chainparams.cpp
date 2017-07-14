// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2013 The Zetacoin developers
// Copyright (c) 2014 The asiccoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

//
// Main network
//

unsigned int pnSeed[] =
{
    0x12345678
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0xf8;
        pchMessageStart[1] = 0xb5;
        pchMessageStart[2] = 0x03;
        pchMessageStart[3] = 0xdf;
        vAlertPubKey = ParseHex("04f09702847840aaf195de8442ebecedf5b095cdbb9bc716bda9110971b28a49e0ead8564ff0db22209e0374782c093bb899692d524e9d6a6956e7c5ecbcd68284");
        nDefaultPort = 14839;
        nRPCPort = 15894;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 950000;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.

        const char* pszTimestamp = "Friday July 14th 2017 9:38PM a new coin was born";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 25 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 2;
        genesis.nTime    = 1499796923;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 0;

        //// debug print
        hashGenesisBlock = genesis.GetHash(); //dont cinnebt out
        while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
           if (++genesis.nNonce==0) break;
           hashGenesisBlock = genesis.GetHash();
        }

        printf("%s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("%x\n", bnProofOfWorkLimit.GetCompact());
        genesis.print();


        assert(hashGenesisBlock == uint256("0x"));
        assert(genesis.hashMerkleRoot == uint256("0x"));

       vSeeds.push_back(CDNSSeedData("162.212.153.103", "162.212.153.103"));

        base58Prefixes[PUBKEY_ADDRESS] = 50;
        base58Prefixes[SCRIPT_ADDRESS] = 9;
        base58Prefixes[SECRET_KEY] = 224;

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time'
            const int64 nTwoDays = 2 * 24 * 60 * 60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nTwoDays) - nTwoDays;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;
