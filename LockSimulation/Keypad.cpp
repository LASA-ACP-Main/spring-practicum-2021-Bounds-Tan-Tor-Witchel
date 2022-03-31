//
// Created by gideo on 3/31/2022.
//

#include "Keypad.h"

void addValue(int value){
    input.push(value);
}

std::string getCode(){
    std::string code = "";
    for(int i = 0; i < input.size(); i++){
        code += input.front();
        input.pop();
    }
}