#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <cctype>

int main(int argc, char** argv){

    std::string comparisonString = "mul(,)";
    std::string doString = "do()";
    std::string dontString = "don't()";
    int result = 0;
    std::vector<std::vector<int>> safetyReports;
    std::ifstream inputFile("input");
    std::string line;

    while (std::getline(inputFile,line)) {

        std::stringstream currentLineStream(line);
        std::string currentWord;
        bool reset = false;
        bool doMult = true;
        int index = 0;
        int numberLength = 0;
        std::string firstMult = "";
        std::string secondMult = "";
        char ch;

        while (currentLineStream.get(ch)) { 

            if(std::isdigit(ch)){
                if(index == 4 || index == 5){
                    if(numberLength<3){
                        if(index == 4){
                           firstMult += ch;
                        }
                        if(index == 5){
                            secondMult += ch;
                        }
                        numberLength++;
                    }else{
                        reset = true;
                    }
                }else{
                    reset = true;
                }
            }else if(ch == comparisonString[index]){
                if(index == comparisonString.size()-1){
                    result += std::stoi(firstMult) * std::stoi(secondMult);
                    reset = true;
                }else{
                    index++;
                    numberLength = 0;
                }
            }else{
                reset = true;
            }
            if(reset){
                index = 0;
                firstMult = "";
                secondMult = "";
                numberLength = 0;
                reset = false;
            }
        }   
    }
    std::cout << "The product is: " << result << std::endl;

    return 0;
}