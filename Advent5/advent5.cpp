#include <vector>
#include <bitset>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <bitset>
#include <iostream>

int main(int argc, char** argv){
    int sum = 0;
    int incorrectSum = 0;
    std::unordered_map<std::string, std::vector<int>> rulesMap;
    std::vector<std::vector<int>> updates;
    bool rulesSection = true;
    char delimiter = ',';
    std::ifstream inputFile("input");
    std::string currentLine;
    while(std::getline(inputFile,currentLine)){
        if(rulesSection){
            if(currentLine.empty()){
                rulesSection = false;
            }else{
                std::string first;
                std::string second;
                for(int i = 0; i < currentLine.size(); i++){                          
                    if(i<2){
                        first += currentLine[i];
                    }
                    if(i>2){
                        second += currentLine[i];
                    }
                }
                if(rulesMap.find(first)==rulesMap.end()){
                    rulesMap[first] = {stoi(second)};
                }else{
                    rulesMap[first].push_back(stoi(second));
                }
            }
        }else{
            std::istringstream stringStream(currentLine);
            std::string number;
            std::bitset<100> bits;
            std::vector<int> update;
            bool skip = false;
            while(std::getline(stringStream, number, delimiter)){
                bool exchanged = false;
                int insertIndex = 100;
                for(int rule : rulesMap[number]){
                    if(bits.test(rule)){
                        exchanged = true;
                        skip = true;
                        for(int i = 0; i<update.size(); i++){
                            if(update[i]==rule){
                                if(i<insertIndex){
                                    insertIndex = i;
                                }
                                break;
                            }
                        }
                    }
                }
                if(exchanged){
                    update.insert(update.begin()+insertIndex, stoi(number));
                }else{
                    update.push_back(stoi(number));
                }
                bits.set(stoi(number));
            }
            if(!skip){
                sum += update[update.size()/2];
            }else{
                incorrectSum += update[update.size()/2];
            }
        }
    }
    std::cout << "Sum of correct updates: " << sum << std::endl;
    std::cout << "Sum of fixed updates: " << incorrectSum << std::endl;
    return 0;
}