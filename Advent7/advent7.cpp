#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

bool isSolvable(std::vector<unsigned long long>& equation, int currentIndex, unsigned long long currentResult){
    if(currentResult > equation[0]){
        return false;
    }
    if(currentIndex == equation.size()){
        return currentResult == equation[0];
    }
    unsigned long long addResult = currentResult + equation[currentIndex];
    unsigned long long multResult = currentResult * equation[currentIndex];

    std::string resultString = std::to_string(currentResult);
    std::string currentString = std::to_string(equation[currentIndex]);
    unsigned long long combinedResult = std::stoull(resultString+currentString);

    return isSolvable(equation, currentIndex+1, addResult) 
            || isSolvable(equation, currentIndex+1, multResult)
            || isSolvable(equation, currentIndex+1, combinedResult);
}

int main(int argc, char** argv){

    unsigned long long sum = 0;
    std::ifstream inputFile("input");
    std::string currentLine;
    std::vector<std::vector<unsigned long long>> equations;
    while(std::getline(inputFile, currentLine)){
        std::istringstream stringStream(currentLine);
        unsigned long long currentNumber;
        std::vector<unsigned long long> currentEquation;
        while(stringStream >> currentNumber){
            currentEquation.push_back(currentNumber);
            if (stringStream.peek() == ':') {
                stringStream.ignore();
            }
        }
        equations.push_back(currentEquation);
    }

    for(auto equation: equations){
        if(isSolvable(equation, 2, equation[1])){
            sum += equation[0];
        }
    }

    std::cout << "Sum of possible equations: " << sum << std::endl;
    return 0;   

}