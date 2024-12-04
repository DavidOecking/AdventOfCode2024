#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


class XmasFinder{
    public:
        XmasFinder() = default;

        int countXmasInFile(std::vector<std::string> xmasList){
            int count = 0;
            std::string xmas = "XMAS";
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

        int countX_masInFile(std::vector<std::string> xmasList){
            int count = 0;
            std::string xmas = "MAS";
            for(int row = 0; row<xmasList.size(); row++){
                for(int column = 0; column<xmasList[row].size(); column++){
                    if(xmasList[row][column]=='A'){
                        if(row >= 1 
                        && column >= 1 
                        && row <= xmasList.size()-2 
                        && column <= xmasList[row].size()-2){
                            if(xmasList[row-1][column-1] == 'M' && xmasList[row+1][column+1] == 'S' 
                            || xmasList[row-1][column-1] == 'S' && xmasList[row+1][column+1] == 'M'){
                                if(xmasList[row-1][column+1] == 'M' && xmasList[row+1][column-1] == 'S' 
                                || xmasList[row-1][column+1] == 'S' && xmasList[row+1][column-1] == 'M'){
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
            return count;
        }

        std::vector<std::string> readXmasFile(const std::string fileName){
            std::vector<std::string> xmasList;
            std::ifstream inputFile(fileName);
            std::string currentLine;
            while(std::getline(inputFile,currentLine)){
                xmasList.push_back(currentLine);
            }
            return xmasList;
        }
};



int main(int argc, char** argv){
    XmasFinder finder;
    auto xmasText = finder.readXmasFile("input");
    int xmasCount = finder.countXmasInFile(xmasText);
    int x_masCount = finder.countX_masInFile(xmasText);
    std::cout << "Number of XMAS in file: " << xmasCount << std::endl;
    std::cout << "Number of X-MAS in file: " << x_masCount << std::endl;
    return 0;
}