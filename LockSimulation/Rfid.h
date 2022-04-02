
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>


#ifndef LOCKSIMULATION_RFID_H
#define LOCKSIMULATION_RFID_H
//this will be replaced with a binary tree in the final implementation
class Rfid {
private:
    std::vector<std::string> authorizedUsers;
    std::string currentCode;
public:
    Rfid(std::string filePath);

    void addUser(std::string userToAdd);

    void removeUser(std::string userToRemove);
    void removeUser(int index);

    std::vector<std::string> getUsers();

    void setCurrentCode(std::string input);

    void shutdown();

    bool isCodeGood();
};

#endif //LOCKSIMULATION_RFID_H
