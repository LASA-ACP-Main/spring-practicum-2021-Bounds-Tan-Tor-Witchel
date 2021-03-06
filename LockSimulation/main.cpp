#include <iostream>
#include "Lock.h"
#include "Rfid.h"
#include "Keypad.h"

//The main idea behind all of this is that there is a very high level of abstraction between main and each individual identification device
//Each device manages itself and only interact with main as a boolean response of valid or invalid.
//Each device should have a "shutdown" method which is called at shutdown to finalize its actions.
//Each device should have a "isCodeGood" method which returns a boolean value depending on if it thinks the lock should be OK to go.


//Notes:
//It would be great if there were a way to make these things happen simultaneously. Someone could type in some keypad input, scan their rfid, finish typing keypad input, and then be have the lock open
//That may only be possible (or at least may be made much easier) when the inputs are separate pieces of hardware, in which case the simulation may be a little flawed.

//Todo:
//require both codes to be inputted within a certain time of each other (15 seconds?)

void shutdownActions(){

}

bool isNum(std::string s){
    if(s == "0" || s == "1" || s == "2" || s == "3" || s == "4" || s == "5" || s == "6" || s == "7" ||
       s == "8" || s == "9"){
        return true;
    }
    return false;
}

bool isNum(char s){
    if(s == '0'  || s == '1' ||  s == '2' ||  s == '3' || s == '4'  || s == '5' || s == '6' || s == '7' ||
       s == '8' || s == '9'){
        return true;
    }
    return false;
}

bool isNumLong(std::string s){
    for(int i = 0; i < s.length(); i++){
        if(!isNum(s[i])){
            return false;
        }
    }
    return true;
}

void getKeypadInput(Keypad* numPad){
    std::string s;
    std::cout << "Keypad Input:" << std::endl;
    while (s != "#") {
        std::cin >> s;
        //This can be deleted outside the simulation because the keypad has a set number of inputs
        if (!isNum(s) && s != "#") {
            std::cout << "Invalid Input" << std::endl;
        }
        else {
            numPad->addValue(s);
        }
    }
}

void getRfidInput(Rfid* rfidScanner){
    std::string s;
    std::cout << "Rfid Input:" << std::endl;
    std::cin >> s;
    if(s.length() != 6 || !isNumLong(s)){
        std::cout << "Invalid Input" << std::endl;
    }
    else {
        rfidScanner->setCurrentCode(stoi(s));
    }
}

void managementMode(Keypad* numPad, Rfid* rfidScanner, Lock* secureLock){
    bool inManagement = true;
    std::vector<std::string> users;
    int toRemove = -1;
    std::string toAdd;
    std::string secretToAdd;
    BST* tree;
    while(inManagement) {
        //Input Loop
        std::cout << "Specify Management Feature" << std::endl;
        std::cout << "0 = Exit and Close Lock, 1 = list RFID Users, 2 = remove RFID User, 3 = add RFID User, 4 = set OTP secret, 5 = Exit without closing the lock" << std::endl;
        int feature;
        std::cin >> feature;
        switch (feature) {
            case 0:
                secureLock->closeLock();
                inManagement = false;
                break;
            case 1:
                tree = rfidScanner->getUsers();
                tree->outputToConsole(tree->root, 0);
                break;
            case 2:
                std::cout << "User Code to Remove: " << std::endl;
                std::cin >> toRemove;
                rfidScanner->removeUser(toRemove);
                break;
            case 3:
                std::cout << "User Code to Add: " << std::endl;
                std::cin >> toAdd;
                rfidScanner->addUser(stoi(toAdd));
                break;
            case 4:
                std::cout << "OTP Secret: " << std::endl;
                std::cin >> secretToAdd;
                numPad->setSecret(secretToAdd);
                break;
            case 5:
                inManagement = false;
                break;
            default:
                std::cout << "Invalid Input" << std::endl;
                break;
        }
    }
}

int main() {

    Keypad* numPad = new Keypad("../OTPSecret.txt");
    Rfid* rfidScanner = new Rfid("../validRFIDs.csv");
    Lock* secureLock = new Lock;

    bool keepRunning = true;
    bool keyCode = true;
    bool rfidCode = true;

    while(keepRunning) {
        //Check to open the lock
        if(keyCode && rfidCode){
            std::cout << "Lock Opened" << std::endl;
            secureLock->openLock();
            keyCode = false;
            rfidCode = false;
        }

        //Input Loop
        std::cout << "Specify device input" << std::endl;
        std::cout << "0 = Shutdown, 1 = Keypad, 2 = Rfid, 3 = Management" << std::endl;
        int purpose;
        std::cin >> purpose;
        switch(purpose) {
            case 0:
                if(!secureLock->getState()){
                    std::cout << "Lock is not Open - you do not have access" << std::endl;
                }
                else {
                    rfidScanner->shutdown();
                    numPad->shutdown();
                    secureLock->shutdown();
                    keepRunning = false;
                }
                break;
            case 1:
                getKeypadInput(numPad);
                keyCode = numPad->isCodeGood();
                break;
            case 2:
                getRfidInput(rfidScanner);
                rfidCode = rfidScanner->isCodeGood();
                break;
            case 3:
                if(!secureLock->getState()){
                    std::cout << "Lock is not Open - you do not have access" << std::endl;
                }
                else {
                    managementMode(numPad, rfidScanner, secureLock);
                }
                break;
            default:
                std::cout << "Invalid Input" << std::endl;
                break;
        }
    }

    return 0;
}
