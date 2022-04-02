
#include <iostream>
#include <queue>
#include <string>

#ifndef LOCKSIMULATION_KEYPAD_H
#define LOCKSIMULATION_KEYPAD_H
class Keypad {
    private:
        std::queue<std::string> input;

        bool codeReady = false;

        std::string secretKey;
    public:
        Keypad(std::string filePath);

        void addValue(std::string value);

        std::string getCode();

        bool isCodeReady();

        void shutdown();

        bool isCodeGood();

};

#endif //LOCKSIMULATION_KEYPAD_H
