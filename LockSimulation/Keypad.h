
#include <iostream>
#include<ostream>
#include<fstream>
#include <queue>
#include <string>
#include "Otp.h"

#ifndef LOCKSIMULATION_KEYPAD_H
#define LOCKSIMULATION_KEYPAD_H
class Keypad {
    private:
        std::queue<std::string> inputs;

        bool codeReady = false;

        Otp* oneTimePass;

        std::string otpFilePath;

        //bool isCodeReady();

        std::string getCode();

        void clear();

public:
        Keypad(std::string filePath);

        void addValue(std::string value);

        void shutdown();

        bool isCodeGood();

        void setSecret(std::string otpSecret);

};

#endif //LOCKSIMULATION_KEYPAD_H
