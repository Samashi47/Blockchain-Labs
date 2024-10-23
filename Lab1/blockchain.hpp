#include<iostream>
#include<vector>
#include<chrono>
#include"digestpp/digestpp.hpp"
using namespace std;

class Block{
    public:
        string hash;
        string data;
        string previousHash;
        int nonce;
        time_t timestamp;
        Block();
        Block(string data, string hash, string previousHash, int nonce, time_t timestamp);
        string printBlock();
};

class Blockchain{
    private:
        vector<Block> chain;
    public:
        Blockchain(string data);
        vector<Block> getChain();
        void printChain();
        void addBlock(string data);
        void mineBlock(Block &block, int difficulty);
};
