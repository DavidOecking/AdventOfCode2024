#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>
#include <unordered_map>
using namespace std;

enum Direction {
    Up,
    Right,
    Down,
    Left
};

std::vector<pair<int,int>> directionValues = {
    {-1,0},
    {0,1},
    {1,0},
    {0,-1}
};

std::pair<int, int>& operator+=(std::pair<int, int>& a, const std::pair<int, int>& b) {
    a.first += b.first;
    a.second += b.second;
    return a;
}

std::pair<int, int>& operator-=(std::pair<int, int>& a, const std::pair<int, int>& b) {
    a.first -= b.first;
    a.second -= b.second;
    return a;
}

Direction& operator++(Direction& dir) {
    dir = static_cast<Direction>((dir + 1) % (Left+1));
    return dir;
}

int countUniqueSpaces(std::pair<int,int> startPosition, Direction startDirection, std::vector<std::string> labMap){
    auto currentPosition = startPosition;
    Direction currentDirection = startDirection;
    bool inBound = true;
    int count = 0;
    int maxCount = labMap.size()*labMap[0].size();
    int repeatCount = 0;

    while(inBound){
        if(repeatCount >= maxCount){
            return -1;
        }
        if(labMap[currentPosition.first][currentPosition.second]=='X'){
            repeatCount++;
        }else{
            labMap[currentPosition.first][currentPosition.second]='X';
            count++;
        }

        currentPosition += directionValues[currentDirection];
        if(currentPosition.first < 0 || currentPosition.first >= labMap.size() || currentPosition.second < 0 || currentPosition.second >= labMap[0].size()){
            inBound = false;
            continue;
        }

        if(labMap[currentPosition.first][currentPosition.second]=='#'){
            currentPosition -= directionValues[currentDirection];
            ++currentDirection;
            continue;
        }
    }

    return count;
}

int main(int argc, char** argv){
    std::vector<std::string> labMap;
    std::pair<int,int> startPosition;
    Direction startDirection;
    std::vector<std::pair<int,int>> obstacles;
    std::ifstream inputFile("input");
    std::string currentLine;
    std::unordered_map<char, Direction> directions = {
        {'^', Up},
        {'v', Down},
        {'>', Right},
        {'<', Left}
    };
    int row = 0;
    while(std::getline(inputFile,currentLine)){
        labMap.push_back(currentLine);
        for(int column = 0; column < currentLine.size(); column++){
            if(currentLine[column] == '#'){
                obstacles.push_back(make_pair(row, column));
                continue;
            }
            for(auto direction: directions){
                if(currentLine[column]==direction.first){
                    startDirection = direction.second;
                    startPosition.first = row;
                    startPosition.second = column;
                    break;
                }
            }
        }
        row++;
    }
    
    int count = countUniqueSpaces(startPosition, startDirection, labMap);
    int numberOfLoops = 0;

    for(int i = 0; i<labMap.size(); i++){
        std::cout << "Line " << i << std::endl;
        for(int j = 0; j<labMap[0].size(); j++){
            auto copiedMap(labMap);
            if(copiedMap[i][j] == '.'){
                copiedMap[i][j] = '#';
                int newCount = countUniqueSpaces(startPosition, startDirection, copiedMap);
                if(newCount==-1){
                    numberOfLoops++;
                }
            }

        }
    }

    std::cout << "Number of steps: " << count << std::endl;
    std::cout << "Number of possible loops:" << numberOfLoops << std::endl;
    return 0;
}