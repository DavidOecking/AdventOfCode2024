#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


class XmasFinder{
    public:
        XmasFinder() = default;

        int countXmasInFile(const std::string fileName){
            int count = 0;
            std::string xmas = "XMAS";
            std::vector<std::string> xmasList = readXmasFile(fileName);
            for(int row = 0; row<xmasList.size(); row++){
                for(int column = 0; column<xmasList[row].size(); column++){
                    char currentChar = xmasList[row][column];
                    if(currentChar == xmas[0]){
                        bool upSpace = row >= 3;
                        bool downSpace = row <= xmasList.size()-4;
                        bool leftSpace = column >= 3;
                        bool rightSpace = column <= xmasList[row].size()-4;

                        if(upSpace){
                            for(int index = 1; index<=3; index++){
                                if(xmasList[row-index][column]!=xmas[index]){
                                    break;
                                }
                                if(index == 3){
                                    count++;
                                }
                            }
                            if(leftSpace){
                                for(int index = 1; index<=3; index++){
                                    if(xmasList[row-index][column-index]!=xmas[index]){
                                        break;
                                    }
                                    if(index == 3){
                                        count++;
                                    }
                                }
                            }
                            if(rightSpace){
                                for(int index = 1; index<=3; index++){
                                    if(xmasList[row-index][column+index]!=xmas[index]){
                                        break;
                                    }
                                    if(index == 3){
                                        count++;
                                    }
                                }
                            }
                        }

                        if(downSpace){
                            for(int index = 1; index<=3; index++){
                                if(xmasList[row+index][column]!=xmas[index]){
                                    break;
                                }
                                if(index == 3){
                                    count++;
                                }
                            }
                            if(leftSpace){
                                for(int index = 1; index<=3; index++){
                                    if(xmasList[row+index][column-index]!=xmas[index]){
                                        break;
                                    }
                                    if(index == 3){
                                        count++;
                                    }
                                }
                            }
                            if(rightSpace){
                                for(int index = 1; index<=3; index++){
                                    if(xmasList[row+index][column+index]!=xmas[index]){
                                        break;
                                    }
                                    if(index == 3){
                                        count++;
                                    }
                                }
                            }
                        }

                        if(leftSpace){
                            for(int index = 1; index<=3; index++){
                                if(xmasList[row][column-index]!=xmas[index]){
                                    break;
                                }
                                if(index == 3){
                                    count++;
                                }
                            }
                        }

                        if(rightSpace){
                            for(int index = 1; index<=3; index++){
                                if(xmasList[row][column+index]!=xmas[index]){
                                    break;
                                }
                                if(index == 3){
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
            return count;
        }

    private:
        std::vector<std::string> readXmasFile(const std::string fileName){
            std::vector<std::string> xmasList;
            std::ifstream inputFile(fileName);
            std::string currentLine;
            while(std::getline(inputFile,currentLine)){
                std::stringstream currentLineStream(currentLine);
                std::string xmasLine;
                char currentCharacter;
                while(currentLineStream >> currentCharacter){
                    xmasLine += currentCharacter;
                }
                xmasList.push_back(xmasLine);
            }
            return xmasList;
        }
};



int main(int argc, char** argv){
    XmasFinder finder;
    int count = finder.countXmasInFile("input");
    std::cout << "Number of XMAS in file: " << count << std::endl;
    return 0;
}