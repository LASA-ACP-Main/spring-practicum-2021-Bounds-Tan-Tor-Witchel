
#include "Keypad.h"

void Keypad::addValue(std::string value) {
    //std::string code = "";
    //for(int i = 0; i < inputs.size()-1; i++){
    //    code += inputs.front();
   // }
    //std:: cout << "addValue Called: " << value << "Total Code: "<< code << std::endl;

    if (inputs.size() > 6) {
        inputs.pop();
    }
    if(value == "#" && inputs.size() >= 6){
        codeReady = true;
    }
    inputs.push(value);

}

std::string Keypad::getCode(){
    std::string code = "";
    int x = inputs.size()-1;
    for(int i = 0; i < x; i++){
        code += (inputs.pop());
    }
    codeReady = false;
    //inputs.clear();
    return code;
}

//bool Keypad::isCodeReady(){
//    return codeReady;
//}

bool Keypad::isCodeGood(){
    if(codeReady){
        //check code against OTP generation
        std::string code = getCode();
        //std::cout << "Padcode: " << code << std::endl;
        //std::cout << oneTimePass->getCode() << std::endl;
        //std::cout << oneTimePass->getLastCode() << std::endl;
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
    inputs.clear();
    return false;
}

Keypad::Keypad(std::string filePath){
    //Read OTP Secret from file
    otpFilePath = filePath;
    std::string secret;
    std::ifstream myFile(filePath);
    if(myFile.is_open()){
        getline(myFile, secret);
    }
    else{
       std::cout << "Failed to read OTP from file" << std::endl;
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



