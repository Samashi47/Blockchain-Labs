#include<iostream>
#include<vector>
#include<map>
#include<ctime>
#include<random>
#include<chrono>
#include"digestpp/digestpp.hpp"
using namespace std;

class BlockPoS{
    public:
        string hash;
        string data;
        string previousHash;
        time_t timestamp;
        string validator;
        BlockPoS();
        BlockPoS(string data, string hash, string previousHash, time_t timestamp, string validator);
        string printBlock();
};

class BlockchainPoS{
    private:
        map<string, int> stakes;
        vector<BlockPoS> chain;
    public:
        BlockchainPoS(string data);
        vector<BlockPoS> getChain();
        void printChain();
        void addBlock(string data);
        void addStake(string validator, int amount);
        string selectValidator();
};