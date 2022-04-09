
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

//bool Keypad::isCodeReady(){
//    return codeReady;
//}

bool Keypad::isCodeGood(){
    if(codeReady){
        //check code against OTP generation
        std::string code = getCode();
        if(code == oneTimePass->getCode() || code == oneTimePass->getLastCode()){
            return true;
        }
        else{
            std::cout << "Code did not match the OTP" << std::endl;
        }
    }
    else{
        std::cout << "Code was not complete" << std::endl;
    }
    return false;
}

Keypad::Keypad(std::string filePath){
    //Read OTP Secret from file
    otpFilePath = filePath;
    std::string secret = "";
    std::ifstream myFile(filePath);
    if(myFile.is_open()){
        getline(myFile, secret);
    }
    else{
        std::cout << "Failed to read OTP from file";
    }
    oneTimePass = new Otp(secret);
    myFile.close();
}

void Keypad::setSecret(std::string otpSecret) {
    oneTimePass->setSecret(otpSecret, otpFilePath);
}

void Keypad::shutdown() {
    //I don't think I need to do anything here
}

