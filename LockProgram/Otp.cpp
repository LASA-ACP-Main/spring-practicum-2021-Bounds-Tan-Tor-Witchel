#include "Otp.h"
//I was going to try to implement the actual TOPT standard but it's pretty complicated so I went with this simple but notaly less secure method.
long long Otp::getTime(){
    std::time_t time = std::time(nullptr);
    return (floor(time/30));
}

Otp::Otp(std::string secretIn){
    secret = (secretIn);
}

std::string Otp::getCode(){
    std::string time = std::to_string(getTime());
    std::string key = secret+time;
    std::hash<std::string> str_hash;
    //the 0s are to ensure there is a start to the code if the hash is small
    key = "000000"+std::to_string(str_hash(key));
    key = key.substr(key.length()-6, key.length());
    return key;
}

std::string Otp::getLastCode(){
    std::string time = std::to_string(getTime()-1);
    std::string key = secret+time;
    std::hash<std::string> str_hash;
    //the 0s are to ensure there is a start to the code if the hash is small
    key = "000000"+std::to_string(str_hash(key));
    key = key.substr(key.length()-6, key.length());
    return key;
}

void Otp::setSecret(std::string input, std::string filePath){
    secret = (input);
    std::ofstream myFile(filePath);
    if (myFile.is_open())
    {
        myFile << secret;
    }
    else{
        std::cout << "failed to write secret to file" << std::endl;
    }
    myFile.close();
}