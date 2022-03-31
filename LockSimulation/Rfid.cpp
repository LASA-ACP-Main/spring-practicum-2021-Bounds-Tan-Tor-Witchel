//
// Created by gideo on 3/31/2022.
//

#include "Rfid.h"

void addUser(std::string userToAdd){
    authorizedUsers.push_back(userToAdd);
}
void removeUser(std::string userToRemove);

std::string getCurrentCode(){
    return currentCode;
}

void setCurrentCode(std::string input){
    currentCode = input;
}
