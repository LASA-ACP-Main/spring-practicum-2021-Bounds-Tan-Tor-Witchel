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
    int getTime();
        long long secret;

    public:
        Otp(std::string secretIn);
        std::string getCode();
        std::string getLastCode();
        void setSecret(std::string input, std::string filePath);

    Otp(Otp *pOtp);
};


#endif //RFID_CPP_OTP_H
