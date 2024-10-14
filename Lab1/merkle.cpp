#include <iostream>
#include <vector>
#include <cmath>
#include "digestpp/digestpp.hpp"

using namespace std;

class Merkle {
    private:
        vector<vector<string>> merkleTree;
    public:
        
        Merkle();

        Merkle(const vector<string> &transactions){
            vector<string> currentLevel = transactions;
            vector<string> nextLevel;
            
            if (currentLevel.size() % 2 != 0){
                currentLevel.push_back(currentLevel.back());
            }
            
            int n = 0;
            int maxDepth = ceil(log2(currentLevel.size())) + 1;

            for (size_t i = 0; i < currentLevel.size(); i++){
                currentLevel[i] = {digestpp::sha256().absorb(currentLevel[i]).hexdigest()};
            }
            
            while ( n < maxDepth ){
                if (currentLevel.size() % 2 != 0 && currentLevel.size() != 1){
                    currentLevel.push_back(currentLevel.back());
                }
                for (size_t i = 0; i < currentLevel.size() -1; i += 2){
                    string generatedHash = {digestpp::sha256().absorb((currentLevel[i] + currentLevel[i + 1])).hexdigest()};
                    nextLevel.push_back(generatedHash);
                }
                merkleTree.push_back(currentLevel);
                currentLevel = nextLevel;
                nextLevel.clear();
                n++;
            }
        }
        
        void printMerkleTree(){
            for (size_t i = 0; i < this->merkleTree.size(); i++){
                cout << "Level " << i << ": " << endl;
                for (size_t j = 0; j < this->merkleTree[i].size(); j++){
                    cout << "\t" <<"H" << i << j << ": "<<this->merkleTree[i][j] << endl;
                }
                cout << endl;
            }
        }

	    string getMerkleRoot(){
            return this->merkleTree.back().back();
        }
};

int main() {
    vector<string> transactions = {"data1", "data2", "data3", "data4", "data5", "data6"};
    Merkle tree(transactions);
    tree.printMerkleTree();
    cout << "Merkle Root: " << tree.getMerkleRoot() << endl;
    return 0;
}