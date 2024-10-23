
#include"blockchain.hpp"


Block::Block(string data, string hash, string previousHash, int nonce, time_t timestamp){
    this->data = data;
    this->hash = hash;
    this->previousHash = previousHash;
    this->nonce = nonce;
    this->timestamp = timestamp;
}

string Block::printBlock(){
    return "\tData: " + this->data + "\n\tHash: " + this->hash + "\n\tPrevious Hash: " + this->previousHash + "\n\tNonce: " + to_string(this->nonce) + "\n\tTimestamp: " + to_string(this->timestamp);
}

Blockchain::Blockchain(string data){
    string hash = digestpp::sha256().absorb(data).hexdigest();
    string previousHash = "0";
    int nonce = 0;
    time_t timestamp = time(0);
    Block genesisBlock(data, hash, previousHash, nonce, timestamp);
    chain.push_back(genesisBlock);
}

vector<Block> Blockchain::getChain(){
    return this->chain;
}

void Blockchain::addBlock(string data){
    string previousHash = chain.back().hash;
    string hash = digestpp::sha256().absorb(data).hexdigest();
    int nonce = 0;
    time_t timestamp = time(0);
    Block newBlock(data, hash, previousHash, nonce, timestamp);
    chain.push_back(newBlock);
}

void Blockchain::printChain(){
    for (size_t i = 0; i < chain.size(); i++){
        cout << "Block " << i << ": " << endl;
        cout << chain[i].printBlock() << endl;
        cout << endl;
    }
}

void Blockchain::mineBlock(Block &block, int difficulty){
    string target(difficulty, '0');
    block.nonce = 0;
    string hash = digestpp::sha256().absorb(block.data + to_string(block.nonce)).hexdigest();;
    while (hash.substr(0, difficulty) != target){
        block.nonce++;
        hash = digestpp::sha256().absorb(block.data + to_string(block.nonce)).hexdigest();
    }
    block.hash = hash;
    cout << "Block mined: " << endl;
    cout << block.printBlock() << endl;
}

int main(){
    
    auto start = std::chrono::high_resolution_clock::now();

    Blockchain blockchain("Genesis Block");
    blockchain.addBlock("Block 1");
    blockchain.addBlock("Block 2");
    blockchain.addBlock("Block 3");
    
    blockchain.mineBlock(blockchain.getChain()[1], 3);
    blockchain.mineBlock(blockchain.getChain()[2], 3);
    blockchain.mineBlock(blockchain.getChain()[3], 3);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    
    blockchain.printChain();
    std::cout << "Time taken to add blocks: " << duration.count() << " seconds" << std::endl;
    
    return 0;
}