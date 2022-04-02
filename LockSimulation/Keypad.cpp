
#include "Keypad.h"

void Keypad::addValue(std::string value) {
    if (input.size() > 7) {
        input.pop();
    }
    if(value == "#" && input.size() == 6){
        codeReady = true;
    }
    input.push(value);
}

std::string Keypad::getCode(){
    std::string code = "";
    for(int i = 0; i < input.size()-1; i++){
        code += input.front();
        input.pop();
    }
    codeReady = false;
    return code;
}

bool Keypad::isCodeReady(){
    return codeReady;
}

bool Keypad::isCodeGood(){
    if(codeReady)
    //check code against OTP generation
}

Keypad::Keypad(std::string filePath){
    //Read OTP Secret from file
}

void Keypad::shutdown() {
    //I don't think this needs to do anything
}