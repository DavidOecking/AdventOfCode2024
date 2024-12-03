#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char** argv){

    std::string comparisonString = "mult(*,*)";
    int result = 1;
    std::vector<std::vector<int>> safetyReports;
    std::ifstream inputFile("input");
    std::string line;
    while (std::getline(inputFile,line)) {
        std::stringstream currentLineStream(line);
        std::string currentWord;
        int currentIndex = 0;
        char ch;
        while (ss.get(ch)) { 
            std::cout << ch << std::endl;
        }   
    }

    return 0;
}