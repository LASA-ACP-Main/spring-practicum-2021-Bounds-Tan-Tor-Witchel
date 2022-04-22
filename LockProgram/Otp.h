#ifndef RFID_CPP_OTP_H
#define RFID_CPP_OTP_H
#include<iostream>
#include<string>
#include <ctime>
#include<cmath>
#include<ostream>
#include<fstream>

class Otp {
    private:
        long long getTime();
        std::string secret;
    public:
        Otp(std::string secretIn);
        std::string getCode();
        std::string getLastCode();
        void setSecret(std::string input, std::string filePath);

};


#endif //RFID_CPP_OTP_H
