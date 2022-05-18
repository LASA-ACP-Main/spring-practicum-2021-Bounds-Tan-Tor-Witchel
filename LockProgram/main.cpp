//g++ *.cpp -lbcm2835 -lwiringPi -lraspicam

//normal imports
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <cstdio>
#include <unistd.h>
#include "Lock.h"
#include "Rfid.h"
#include "Keypad.h"
#include "MFRC522.h"
extern "C" {
#include <wiringPi.h>
}

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
#define pathToManagementInput "managementIn.txt"

//wiringPi numbers, NOT BCM
#define L1 23
#define L2 25
#define L3 22
#define L4 31

#define C1 26
#define C2 27
#define C3 28
#define C4 29

//RFID Reset pin = 22
//RFID SCK Pin = 24 (I think, that may be SDA)

void readLine(int line,std::string characters[4], std::string* keypadOut){
    digitalWrite(line, 1);

    //some of this is very broken - current is leaking between them
    if(digitalRead(C4) == 1){
        //std::cout << (characters[3]) << std::endl;
        //delay(100);
    }
    if(digitalRead(C3) == 1){
        std::cout << (characters[2]) << std::endl;
        *keypadOut = characters[2];
        delay(100);
    }
    if(digitalRead(C2) == 1){
        std::cout << (characters[1]) << std::endl;
        *keypadOut = characters[1];
        delay(100);
    }
    if(digitalRead(C1) == 1){
        std::cout << (characters[0]) << std::endl;
        *keypadOut = characters[0];
        delay(100);
    }
    digitalWrite(line, 0);
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
                    rfidScanner->removeUser(stoi(toRemove));
                    std::cout << "Removed from RFID Users " << toRemove << std::endl;
                    break;
                case 2:
                    toAdd = x.substr(1, x.length() - 1);
                    rfidScanner->addUser(stoi(toAdd));
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
    //init
    wiringPiSetup();

    Keypad* numPad = new Keypad("OTPSecret.txt");
    Rfid* rfidScanner = new Rfid("validRFIDs.csv");
    Lock* secureLock = new Lock;

    bool* keepRunning = new bool;
    *keepRunning = true;
    bool* keyCode = new bool;
    *keyCode = false;
    bool* rfidCode = new bool;
    *rfidCode = false;
    std::string* keypadCurrent = new std::string;
    *keypadCurrent = "";

    pinMode(L1, OUTPUT);
    pinMode(L2, OUTPUT);
    pinMode(L3, OUTPUT);
    pinMode(L4, OUTPUT);

    pinMode(C1, INPUT);
    pinMode(C2, INPUT);
    pinMode(C3, INPUT);
    pinMode(C4, INPUT);

    pullUpDnControl(C1,  PUD_DOWN);
    pullUpDnControl(C2,  PUD_DOWN);
    pullUpDnControl(C3,  PUD_DOWN);
    pullUpDnControl(C4,  PUD_DOWN);

    std::string line1[4] = {"1","2","3","A"};
    std::string line2[4] = {"4","5","6","B"};
    std::string line3[4] = {"7","8","9","C"};
    std::string line4[4] = {"*","0","#","D"};

    MFRC522 rfid;
    rfid.PCD_Init();
    std::string UID;


    //running loop
    while(*keepRunning) {
        //Check to open the lock
        if(*keyCode && *rfidCode){
            std::cout << "Lock Opened" << std::endl;
            secureLock->openLock();
            *keyCode = false;
            *rfidCode = false;
        }

        //Input Loop
        //get RFID input
        if(!rfid.PICC_IsNewCardPresent()){}

        else if( !rfid.PICC_ReadCardSerial()){}

        else{
            UID = "";
            // Print UID
            for(byte i = 0; i < rfid.uid.size; ++i){
                if(rfid.uid.uidByte[i] < 0x10){
                    UID+=" 0";
                    UID+= to_string(rfid.uid.uidByte[i]);
                }
                else{
                    UID+= " ";
                    UID+= to_string(rfid.uid.uidByte[i]);
                }
            }
            cout << UID << "\n";
            delay(500);
        
        //parse RFID input
        std::hash<std::string> str_hash;
        //the 0s are to ensure there is a start to the code if the hash is small
        UID = "000000"+std::to_string(str_hash(UID));
        int rfidIn = stoi(UID.substr(UID.length()-6, UID.length()));
        rfidScanner->setCurrentCode(rfidIn);
		}

        //get Keypad input
        readLine(L1, line1, keypadCurrent);
        readLine(L2, line2, keypadCurrent);
        readLine(L3, line3, keypadCurrent);
        readLine(L4, line4, keypadCurrent);
        delay(100);
        //parse Keypad input
            if(*keypadCurrent == "*"){
                *rfidCode = false;
                *keyCode = false;
                rfidScanner->isCodeGood();
                numPad->isCodeGood();
                secureLock->closeLock();
            }
            else if(*keypadCurrent == "#"){
                numPad->addValue("#");
                *keyCode = numPad->isCodeGood();
                *rfidCode = rfidScanner->isCodeGood();
            }
            else if (*keypadCurrent != ""){
                numPad->addValue(*keypadCurrent);
            }
            *keypadCurrent = "";

        //this is just to make sure it isn't going crazy on the disk. The delay is arbitrary and can be changed.
        delay(100);
        checkManagementMode(numPad, rfidScanner, secureLock, keepRunning);
    }
    return 0;
}
