#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>  
#include <array>

enum Direction {
    Ascending,
    Descending
};

bool isSafe(Direction direction, int currentNumber, int previousNumber){
    if(direction == Descending && currentNumber<previousNumber){
        return abs(currentNumber-previousNumber)<=3;
    }
    if(direction == Ascending && currentNumber>previousNumber){
        return abs(currentNumber-previousNumber)<=3;
    }
    return false;
}

int main(int argc, char** argv){

    int safeCount = 0;
    std::vector<std::array<int, 5>> safetyReports;
    std::ifstream inputFile("input");
    std::string line;
    while (std::getline(inputFile,line)) {
        std::stringstream currentLineStream(line);
        int currentNumber;
        std::array<int, 5> currentReport = {};
        int index = 0;
        bool safe = false;
        Direction direction;

        while(currentLineStream >> currentNumber){
            if(index == 1){
                if(currentNumber<currentReport[0] && abs(currentNumber-currentReport[index-1])<=3){
                    direction = Descending;
                    safe = true;
                }else if(currentNumber>currentReport[0] && abs(currentNumber-currentReport[index-1])<=3){
                    direction = Ascending;
                    safe = true;
                }
            }else if(safe){
                safe = isSafe(direction, currentNumber, currentReport[index-1]);
            }
            currentReport[index] = currentNumber;
            index++;
        }

        if(safe){ safeCount++; }
        safetyReports.push_back(currentReport);
    }

    std::cout << "Number of safe reports: " << safeCount << std::endl;
    return 0;
}