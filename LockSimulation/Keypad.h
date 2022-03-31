//
// Created by gideo on 3/31/2022.
//
#include <iostream>
#include <queue>
#include <string>

#ifndef LOCKSIMULATION_KEYPAD_H
#define LOCKSIMULATION_KEYPAD_H

std::queue<int> input;
void addValue(int value);
std::string getCode();

#endif //LOCKSIMULATION_KEYPAD_H
