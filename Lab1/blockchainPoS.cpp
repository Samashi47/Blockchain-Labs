#include"blockchainPoS.hpp"

BlockPoS::BlockPoS(string data, string hash, string previousHash, time_t timestamp, string validator){
    this->data = data;
    this->hash = hash;
    this->previousHash = previousHash;
    this->timestamp = timestamp;
    this->validator = validator;
}

string BlockPoS::printBlock(){
    return "\tData: " + this->data + "\n\tHash: " + this->hash + "\n\tPrevious Hash: " \
        + this->previousHash + "\n\tTimestamp: " + to_string(this->timestamp) + "\n\tValidator: " + this->validator;
}

BlockchainPoS::BlockchainPoS(string data){
    string hash = digestpp::sha256().absorb(data).hexdigest();
    string previousHash = "0";
    int nonce = 0;
    time_t timestamp = time(0);
    string validator = "Genesis";
    BlockPoS genesisBlock(data, hash, previousHash, timestamp, validator);
    chain.push_back(genesisBlock);
}

vector<BlockPoS> BlockchainPoS::getChain(){
    return this->chain;
}

void BlockchainPoS::addBlock(string data){
    string previousHash = chain.back().hash;
    string hash = digestpp::sha256().absorb(data).hexdigest();
    int nonce = 0;
    time_t timestamp = time(0);
    string validator = selectValidator();
    BlockPoS newBlock(data, hash, previousHash, timestamp, validator);
    chain.push_back(newBlock);
}

void BlockchainPoS::printChain(){
    for (size_t i = 0; i < chain.size(); i++){
        cout << "Block " << i << ": " << endl;
        cout << chain[i].printBlock() << endl;
        cout << endl;
    }
}

map<string, int> BlockchainPoS::getStakes(){
    return this->stakes;
}


void BlockchainPoS::addStake(string validator, int amount){
    stakes[validator] += amount;
}

string BlockchainPoS::selectValidator(){
    int totalStake = 0;
    for (auto const& stake : stakes){
        totalStake += stake.second;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, totalStake);

    int selection = dist(gen);
    int cumulativeStake = 0;
    
    for (auto const& stake : stakes){
        cumulativeStake += stake.second;
        if (selection <= cumulativeStake) {
            return stake.first;
        }
    }
    return "Mr. X";
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();

    BlockchainPoS blockchain("Genesis Block");

    for(int i = 0; i < 6; i++){
        blockchain.addStake("Validator" + to_string(i), (rand() % 1000) + 1);
    }

    blockchain.addBlock("Block 1");
    blockchain.addBlock("Block 2");
    blockchain.addBlock("Block 3");

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    blockchain.printChain();
    
    std::cout << "Time taken to add blocks: " << duration.count() << " seconds" << std::endl;

    cout << "Stakes:" << endl;
    for (const auto& stake : blockchain.getStakes()) {
        cout << "Validator: " << stake.first << ", Stake: " << stake.second << endl;
    }
    

    return 0;
}