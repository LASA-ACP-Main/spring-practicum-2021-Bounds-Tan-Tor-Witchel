
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
    rfidFilePath = filePath;
    vector<vector<string>> csvArr = parseCSV(ifstream(filePath));
    authorizedUsers = csvArr[0];
}

bool Rfid::isCodeGood(){
    //compare current code to the list of valid codes
    //This linear search will be replaced with a binary tree search in the final version (once we implement that data structure)
    for(int i = 0; i < authorizedUsers.size(); i++){
        if(authorizedUsers[i] == currentCode){
            return true;
        }
    }

    return false;
}

void Rfid::shutdown(){
    //write all valid RFIDs to file
    auto out = ofstream(rfidFilePath);
    for (auto y : authorizedUsers) {
        out << y << ",";
    }
    out.close();
}