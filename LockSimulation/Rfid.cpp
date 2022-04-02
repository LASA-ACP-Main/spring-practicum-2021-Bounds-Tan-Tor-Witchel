
#include "Rfid.h"



void Rfid::addUser(std::string userToAdd){
    authorizedUsers.push_back(userToAdd);
}

void Rfid::removeUser(std::string userToRemove){
    authorizedUsers.erase(std::remove(authorizedUsers.begin(), authorizedUsers.end(), userToRemove), authorizedUsers.end());
}

void Rfid::removeUser(int index){
    authorizedUsers.erase(authorizedUsers.begin()+index);
}

std::vector<std::string> Rfid::getUsers(){
    return authorizedUsers;
}



void Rfid::setCurrentCode(std::string input){
    currentCode = input;
}

Rfid::Rfid(std::string filePath){
    //read valid RFIDs from file and add them to authorizedUsers
}

bool Rfid::isCodeGood(){
//compare current code to the list of valid codes
}

void Rfid::shutdown(){
    //write all valid RFIDs to file
}