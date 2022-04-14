#include "Otp.h"
//I was going to try to implement the actual TOPT standard but it's pretty complicated so I went with this simple but notaly less secure method.
int Otp::getTime(){
    std::time_t time = std::time(nullptr);
    return floor(time/30);
}

Otp::Otp(std::string secretIn){
    secret = stoll(secretIn);
}

std::string Otp::getCode(){
    int time = getTime();
    long long key = secret*time;
    key = key%1000000;
    return std::to_string(key);
}

std::string Otp::getLastCode(){
    int time = getTime()-1;
    long long key = secret*time;
    key = key%1000000;
    return std::to_string(key);
}

void Otp::setSecret(std::string input, std::string filePath){
    secret = stoi(input);
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
