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
//where is that second data structure coming in again? custom queue?

bool checkCredentials(std::string keyCode, std::string rfidCode){

}

void shutdownActions(){

}

void getKeypadInput(Keypad* numPad){
    std::string s;
    std::cout << "Keypad Input:" << std::endl;
    while (s != "#") {
        std::cin >> s;
        //This can be deleted outside the simulation because the keypad has a set number of inputs
        if (s != "0" && s != "1" && s != "2" && s != "3" && s != "4" && s != "5" && s != "6" && s != "7" &&
            s != "8" && s != "9" && s != "#") {
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
    rfidScanner->setCurrentCode(s);
}

void managementMode(Keypad* numPad, Rfid* rfidScanner, Lock* secureLock){
    bool inManagement = true;
    std::vector<std::string> users = rfidScanner->getUsers();
    int toRemove = -1;
    std::string toAdd;
    std::string secretToAdd;
    while(inManagement) {
        //Input Loop
        std::cout << "Specify Management Feature" << std::endl;
        std::cout << "0 = Exit and Close Lock, 1 = list RFID Users, 2 = remove RFID User, 3 = add RFID User, 4 = set OTP secret" << std::endl;
        int feature;
        std::cin >> feature;
        switch (feature) {
            case 0:
                secureLock->closeLock();
                inManagement = false;
                break;
            case 1:
                std::cout << "Users: "<< std::endl;
                for(int i = 0; i < users.size(); i++){
                    std::cout << "[" << i << "] " << users[i] << std::endl;
                }
                break;
            case 2:
                std::cout << "User Code to Remove: " << std::endl;
                std::cin >> toRemove;
                if(toRemove < 0 || toRemove >= users.size()){
                    std::cout << "Not in Range" << std::endl;
                }
                else{
                    rfidScanner->removeUser(toRemove);
                }
                break;
            case 3:
                std::cout << "User Code to Add: " << std::endl;
                std::cin >> toAdd;
                rfidScanner->addUser(toAdd);
                break;
            case 4:
                std::cout << "OTP Secret: " << std::endl;
                std::cin >> secretToAdd;
                numPad->setSecret(secretToAdd);
                break;
        }
    }
}

int main() {
    Keypad* numPad = new Keypad("OPTSecret.txt");
    Rfid* rfidScanner = new Rfid("validRFIDs.txt");
    Lock* secureLock = new Lock;

    bool keepRunning = true;
    bool keyCode = false;
    bool rfidCode = false;

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

        }
    }

    return 0;
}
