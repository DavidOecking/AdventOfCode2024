#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>  
#include <array>
#include <algorithm>
#include <utility> 
#include <cmath>

enum Direction {
    Unitialized,
    Ascending,
    Descending,
    Equal,
};

bool isDistanceSafe(int first, int second){
    return abs(first-second)<=3;
}

Direction getDirection(int firstNumber, int secondNumber){
    if(firstNumber==secondNumber){
        return Equal;
    }
    return (firstNumber<secondNumber)?Ascending:Descending;
}

bool isSafe(Direction direction, int currentNumber, int previousNumber){
    if(direction == Descending && currentNumber<previousNumber){
        return isDistanceSafe(currentNumber, previousNumber);
    }
    if(direction == Ascending && currentNumber>previousNumber){
        return isDistanceSafe(currentNumber, previousNumber);
    }
    return false;
}

bool isSafeWithDampener(std::vector<int>& report, bool levelRemoved = false){
    bool currentDirection;
    Direction startDirection = getDirection(report[0],report[1]);

    for(int i = 1; i<report.size(); i++){
        Direction currentDirection = getDirection(report[i-1],report[i]);
        if(!isDistanceSafe(report[i],report[i-1]) || currentDirection != startDirection){
            if(levelRemoved){
                return false;
            }

            std::vector<int> previousLevelRemovedReport = report;
            previousLevelRemovedReport.erase(previousLevelRemovedReport.begin()+i-1);
            bool safeWithoutPrevious =  isSafeWithDampener(previousLevelRemovedReport, true);

            std::vector<int> currentLevelRemovedReport = report;
            currentLevelRemovedReport.erase(currentLevelRemovedReport.begin()+i);
            bool safeWithoutCurrent =  isSafeWithDampener(currentLevelRemovedReport, true);
            return safeWithoutCurrent || safeWithoutPrevious;
       }
    }
    return true;
}

bool isDampenerSafe(std::vector<int>& report){
    return isSafeWithDampener(report);
}


int main(int argc, char** argv){

    int safeCount = 0;
    std::vector<std::vector<int>> safetyReports;
    std::ifstream inputFile("input");
    std::string line;
    while (std::getline(inputFile,line)) {
        std::stringstream currentLineStream(line);
        int currentNumber;
        std::vector<int> currentReport;
        int index = 0;
        bool safe = false;
        Direction direction;

        while(currentLineStream >> currentNumber){
            currentReport.push_back(currentNumber);
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
            index++;
        }

        if(safe){ safeCount++; }
        safetyReports.push_back(currentReport);
    }

    int dampenedSafeCount = 0;
    dampenedSafeCount = std::count_if(safetyReports.begin(), safetyReports.end(), isDampenerSafe);
    std::cout << "Number of safe reports: " << safeCount << std::endl;
    std::cout << "Number of safe reports with Dampener: " << dampenedSafeCount << std::endl;
    return 0;
}