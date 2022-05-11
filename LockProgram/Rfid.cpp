#include "Rfid.h"


void Rfid::addUser(int userToAdd){
    Bnode* user = new Bnode;
    user->key_value = userToAdd;
    user->p_left = nullptr;
    user->p_right = nullptr;
    authorizedUsers->insert(authorizedUsers->root, user);
}

void Rfid::removeUser(int userToRemove){
    authorizedUsers->remove(userToRemove);
}

BST* Rfid::getUsers(){
    return authorizedUsers;
}


void Rfid::setCurrentCode(int input){
    currentCode = input;
}

Rfid::Rfid(std::string filePath){
    rfidFilePath = filePath;
    vector<vector<string>> csvArr = parseCSV(ifstream(filePath));
    for(auto x : csvArr){
        for(auto y : x){
            Bnode* user = new Bnode;
            user->key_value = stoi(y);
            user->p_left = nullptr;
            user->p_right = nullptr;
            authorizedUsers->insert(authorizedUsers->root, user);
        }
    }
}

bool Rfid::isCodeGood(){
    //compare current code to the list of valid codes
    //This linear search will be replaced with a binary tree search in the final version (once we implement that data structure)
    Bnode** parent = new Bnode*;
    Bnode** location = new Bnode*;
    authorizedUsers->find(currentCode, parent, location);
    if(*location == nullptr) {
        cout << "Code is not authorized" << endl;
        currentCode = 000000;
        return false;
    }
    cout << "Authorized Code Accepted" << endl;
    currentCode = 000000;
    return true;
}

void Rfid::shutdown(){
    //write all valid RFIDs to file
    authorizedUsers->outputAsCSV(rfidFilePath);
}