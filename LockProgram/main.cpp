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
//custom binary tree implementation for RFIDs
//require both codes to be inputted within a certain time of each other (15 seconds?)
#define pathToRfidInput "rfidIn.txt"
#define pathToNumpadInput "numpadIn.txt"
#define pathToManagementInput "managementIn.txt"

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
    std::string keypadRaw = "";
    std::fstream keypadFile(pathToNumpadInput);
    if (keypadFile.is_open() && !keypadFile.eof())
    {
        //read
        getline(keypadFile, keypadRaw);
    }
    else{
        std::cout << "failed to read keypadRaw from file" << std::endl;
        return;
    }
    keypadFile.close();

    //clear
    std::ofstream clearing(pathToNumpadInput);
    clearing.close();

    if(keypadRaw.empty()){
        return;
    }

    for(char x : keypadRaw){
        if(x == '#'){
            numPad->addValue("#");
            break;
        }

        if (!isNum(x)) {
            std::cout << "Invalid Keypad Input" << std::endl;
        }
        else {
            numPad->addValue(std::string(1,x));
        }
    }
}

void getRfidInput(Rfid* rfidScanner){
    std::string rfidRaw = "";
    std::fstream rfidFile(pathToRfidInput);
    if (rfidFile.is_open() && !rfidFile.eof())
    {
        //read
        getline(rfidFile, rfidRaw);
    }
    else{
        std::cout << "failed to read rfidRaw from file" << std::endl;
        return;
    }
    rfidFile.close();

    //clear
    std::ofstream clearing(pathToRfidInput);
    clearing.close();

    if(rfidRaw.empty()){
        return;
    }

    if(rfidRaw.length() != 6 || !isNumLong(rfidRaw)){
        std::cout << "Invalid Input" << std::endl;
    }
    else {
        rfidScanner->setCurrentCode(rfidRaw);
    }
}

void checkManagementMode(Keypad* numPad, Rfid* rfidScanner, Lock* secureLock, bool* keepRunning){
    std::vector<std::string> managementRaw;
    std::string* temp;
    int counter = 0;
    std::fstream managementFile(pathToManagementInput);
    if(!managementFile.is_open() || managementFile.eof()){
        std::cout << "failed to read managementRaw from file" << std::endl;
        return;
    }
    while (managementFile.is_open() && !managementFile.eof())
    {
        //read
        temp = new std::string;
        getline(managementFile, *temp);
        managementRaw.push_back(*temp);
    }
    managementFile.close();


    //clear
    std::ofstream clearing(pathToManagementInput);
    clearing.close();

    if(managementRaw.empty()){
        return;
    }

    std::vector<std::string> users;
    std::string toRemove = "";
    std::string toAdd;
    std::string secretToAdd;
    for(std::string x : managementRaw) {
        if (x != "") {
            int feature = stoi(x.substr(0, 1));
            switch (feature) {
                case 0:
                    std::cout << "Shutdown" << std::endl;
                    rfidScanner->shutdown();
                    numPad->shutdown();
                    secureLock->shutdown();
                    *keepRunning = false;
                    break;
                case 1:
                    toRemove = x.substr(1, x.length() - 1);
                    rfidScanner->removeUser(toRemove);
                    std::cout << "Removed from RFID Users " << toRemove << std::endl;
                    break;
                case 2:
                    toAdd = x.substr(1, x.length() - 1);
                    rfidScanner->addUser(toAdd);
                    std::cout << "Added to RFID Users " << toAdd << std::endl;
                    break;
                case 3:
                    secretToAdd = x.substr(1, x.length() - 1);
                    numPad->setSecret(secretToAdd);
                    std::cout << "Set OTP Secret to " << secretToAdd << std::endl;
                    break;
                default:
                    std::cout << "Invalid Input" << std::endl;
                    break;
            }
        }
    }
}

int main() {

    Keypad* numPad = new Keypad("../OTPSecret.txt");
    Rfid* rfidScanner = new Rfid("../validRFIDs.csv");
    Lock* secureLock = new Lock;

    bool* keepRunning = new bool;
    *keepRunning = true;
    bool keyCode = false;
    bool rfidCode = false;

    while(*keepRunning) {
        //Check to open the lock
        if(keyCode && rfidCode){
            std::cout << "Lock Opened" << std::endl;
            secureLock->openLock();
            keyCode = false;
            rfidCode = false;
        }

        //Input Loop
        getRfidInput(rfidScanner);
        rfidCode = rfidScanner->isCodeGood();
        getKeypadInput(numPad);
        keyCode = numPad->isCodeGood();
        checkManagementMode(numPad, rfidScanner, secureLock, keepRunning);

    }
    return 0;
}
