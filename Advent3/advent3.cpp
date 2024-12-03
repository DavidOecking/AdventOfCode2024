#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <cctype>

enum CurrentOperation{
    Uninitialized,
    Mult,
    Do,
    Dont
};

int main(int argc, char** argv){

    std::string mulString = "mul(,)";
    std::string doString = "do()";
    std::string dontString = "don't()";
    int result = 0;
    int conditionalResult = 0;
    std::vector<std::vector<int>> safetyReports;
    std::ifstream inputFile("input");
    std::string line;
    CurrentOperation currentOperation = Uninitialized;
    std::string currentWord;
    bool reset = false;
    bool doMult = true;
    int index = 0;
    int numberLength = 0;
    std::string firstMult = "";
    std::string secondMult = "";

    while (std::getline(inputFile,line)) {

        std::stringstream currentLineStream(line);

        char ch;

        while (currentLineStream.get(ch)) { 

            if(currentOperation == Uninitialized){
                if(ch == mulString[index]){
                    currentOperation = Mult;
                }else if(ch == doString[index]){
                    currentOperation = Do;
                }
            }

            if(currentOperation == Do){
                if(ch == doString[index]){
                    if(index == doString.size()-1){
                        doMult = true;
                        reset = true;
                    }
                    index++;
                }else if(index == 2 && ch == dontString[index]){
                    currentOperation = Dont;
                }else{
                    reset = true;
                }
            }

            if(currentOperation == Dont){
                if(ch == dontString[index]){
                    if(index == dontString.size()-1){
                        doMult = false;
                        reset = true;
                    }
                    index++;
                }else{
                    reset = true;
                }
            }

            if(currentOperation == Mult){
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
                }else if(ch == mulString[index]){
                    if(index == mulString.size()-1){
                        int first = std::stoi(firstMult);
                        int second = std::stoi(secondMult);
                        if(doMult){
                            conditionalResult += first * second; 
                        }
                        result += first * second; 
                        reset = true;
                    }else{
                        index++;
                        numberLength = 0;
                    }
                }else{
                    reset = true;
                }
            }
            
            if(reset){
                index = 0;
                firstMult = "";
                secondMult = "";
                numberLength = 0;
                currentOperation = Uninitialized;
                reset = false;
            }
        }   
    }
    std::cout << "The product is: " << result << std::endl;
    std::cout << "The conditional product is: " << conditionalResult << std::endl;
    return 0;
}