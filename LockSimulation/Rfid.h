
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <fstream>
#include "csvManager.h"
#include "BSTree.h"

#ifndef LOCKSIMULATION_RFID_H
#define LOCKSIMULATION_RFID_H
//this will be replaced with a binary tree in the final implementation
class Rfid {
private:
    BST* authorizedUsers = new BST;
    int currentCode;
    std::string rfidFilePath;
public:
    Rfid(std::string filePath);

    void addUser(int userToAdd);

    void removeUser(int userToRemove);

    BST* getUsers();

    void setCurrentCode(int input);

    void shutdown();

    bool isCodeGood();
};

#endif //LOCKSIMULATION_RFID_H