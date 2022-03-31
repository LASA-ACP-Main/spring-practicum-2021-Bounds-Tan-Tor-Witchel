//
// Created by gideo on 3/31/2022.
//
#include<iostream>
#include<string>
#include<vector>


#ifndef LOCKSIMULATION_RFID_H
#define LOCKSIMULATION_RFID_H
//this will be replaced with a binary tree in the final implementation
std::vector<std::string> authorizedUsers;
std::string currentCode;
void addUser(std::string userToAdd);
void removeUser(std::string userToRemove);

std::string getCurrentCode();
void setCurrentCode(std::string input);

#endif //LOCKSIMULATION_RFID_H
