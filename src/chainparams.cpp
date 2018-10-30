// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin developers
// Copyright (c) 2017 Empinel/The Ion Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "amount.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, const uint64_t nTime, const uint32_t nNonce, const uint32_t nBits, const int32_t nVersion, const CAmount& genesisReward)
{
	std::vector<CTxIn> vin;
	vin.resize(1);
	vin[0].scriptSig = CScript() << nTime << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
	std::vector<CTxOut> vout;
	vout.resize(1);
	vout[0].nValue = genesisReward;
	vout[0].scriptPubKey = genesisOutputScript;
	CTransaction txNew(1, nTime, vin, vout, 0);
		
    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = genesis.BuildMerkleTree();

    return genesis;
}

static CBlock CreateGenesisBlock(uint64_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
	const char* pszTimestamp = "Vdoo";
    const CScript genesisOutputScript = CScript() << ParseHex("") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa5;
        pchMessageStart[1] = 0xb4;
        pchMessageStart[2] = 0xc3;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("");
        nDefaultPort = 19001;
        nRPCPort = 19002;
        nProofOfWorkLimit = uint256S("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        nProofOfStakeLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

		genesis = CreateGenesisBlock(1528034356, 73573652, 503382015, 1, (1 * COIN));
		

		
		hashGenesisBlock = genesis.GetHash();
		
      //uint256 hashTarget = CBigNum().SetCompact(block.nBits).getuint256();
      /* uint256 hashTarget = uint256().SetCompact(genesis.nBits);
        while (genesis.GetHash()> hashTarget)
        {
            if (genesis.nNonce % 1048576 == 0)
                printf("n=%dM hash=%s\n", genesis.nNonce / 1048576,
                       genesis.GetHash().ToString().c_str());
            genesis.nNonce++;
        }

        hashGenesisBlock = genesis.GetHash(); 


		LogPrintf("genesis.hashGenesisBlock == %s\n", genesis.GetHash().ToString().c_str());
		LogPrintf("genesis.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
		LogPrintf("genesis.nBits == %d\n", genesis.nBits);
		LogPrintf("genesis.nNonce == %d\n", genesis.nNonce); */
	
        assert(hashGenesisBlock == uint256("0x000000f1e56a68f950793fee28f96cdd934f12600ad7641978c04c26d9c8bc37"));
        assert(genesis.hashMerkleRoot == uint256("0xa28ab2ba8cb43f67263733cf646e50bffbfc27f1de253fca348e62ac29eba369"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,70);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,90);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,178);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

	   vSeeds.push_back(CDNSSeedData("bca100.com", "bca100.com"));
       vSeeds.push_back(CDNSSeedData("bca100.net", "bca100.net"));
       
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

		nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "VTRbC1gffYLXN1Ni3WE9YecBQPqWjNq8qC";
        nLastPOWBlock 	= 30000;
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


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x2f;
        pchMessageStart[1] = 0xca;
        pchMessageStart[2] = 0x4e;
        pchMessageStart[3] = 0x3e;
        vAlertPubKey = ParseHex("");
        nDefaultPort = 27170;
        nRPCPort = 27171;
        strDataDir = "testnet";
   
        nProofOfWorkLimit = uint256S("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        nProofOfStakeLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

		genesis = CreateGenesisBlock(1528034356, 73573652 , 503382015, 1, (1 * COIN));


		hashGenesisBlock = genesis.GetHash();
     /*  uint256 hashTarget = uint256().SetCompact(genesis.nBits);
        while (genesis.GetHash()> hashTarget)
        {
            if (genesis.nNonce % 1048576 == 0)
                printf("n=%dM hash=%s\n", genesis.nNonce / 1048576,
                       genesis.GetHash().ToString().c_str());
            genesis.nNonce++;
        }

        hashGenesisBlock = genesis.GetHash(); 
		LogPrintf("genesis.hashGenesisBlock == %s\n", genesis.GetHash().ToString().c_str());
		LogPrintf("genesis.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
		LogPrintf("genesis.nBits == %d\n", genesis.nBits);
		LogPrintf("genesis.nNonce == %d\n", genesis.nNonce); */
		
        assert(hashGenesisBlock == uint256("0x000000f1e56a68f950793fee28f96cdd934f12600ad7641978c04c26d9c8bc37"));
        assert(genesis.hashMerkleRoot == uint256("0xa28ab2ba8cb43f67263733cf646e50bffbfc27f1de253fca348e62ac29eba369"));
                
        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,97);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
