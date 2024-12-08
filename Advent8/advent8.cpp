#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <bitset>
#include <unordered_map>

int main(int argc, char** argv){

    std::ifstream inputFile("testInput");
    std::string currentLine;
    std::vector<std::string> cityMap;
    std::vector<std::vector<bool>> antinodes;
    std::unordered_map<char, std::vector<int,int>> antennas;
    int row = 0;
    while(std::getline(inputFile, currentLine)){
        for(int column = 0; column<currentLine.size(); column++){
            char currentChar = currentLine[column];
            if(currentChar != '.'){
                if(antennas.find(currentChar)==antennas.end()){
                    antennas[currentChar] = {(row, column)};
                }else{
                    antennas[currentChar].push_back((row, column));
                }
            }
        }
        row++;
        cityMap.push_back(currentLine);
    }
    return 0;
}