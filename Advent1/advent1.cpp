#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>  
#include <cmath>

void insertSorted(std::vector<int>& list, int value){
    for(size_t i = 0; i<list.size(); ++i) {
        if(value<list[i]){
            list.insert(list.begin()+i,value);
            return;
        }
    }
    list.push_back(value);
}

int main(int argc, char** argv){

    int difference = 0;
    std::vector<int> left, right;

    std::ifstream inputFile("input");
    std::string line;
    while (std::getline(inputFile,line)) {
        std::stringstream currentLineStream(line);
        std::string word;
        int index = 0;
        int first = 0, second = 0;

        currentLineStream >> first;
        currentLineStream >> second;

        insertSorted(left, first);
        insertSorted(right, second);
    }
    for(size_t i = 0; i<left.size(); ++i){
        difference += std::abs(left[i]-right[i]);
    }
    std::cout << "Difference: ";
    std::cout << difference;
    std::cout << std::endl; 
    return 0;
}

