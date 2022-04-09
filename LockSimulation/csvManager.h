#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#ifndef RFID_CPP_CSVMANAGER_H
#define RFID_CPP_CSVMANAGER_H

using namespace std;
vector<string> parseLine(string str);
vector<vector<string>> parseCSV(ifstream myFile);
void print2dArray(vector<vector<string>> in);
void output2dArray(vector<vector<string>> in, ofstream out);
vector<vector<string>> sort2dArray(vector<vector<string>> in, int col);
void printCol(vector<vector<string>> in, int col);
void printCleanCol(vector<vector<string>> in, int col);
void printRow(vector<vector<string>> in, int row);

#endif //RFID_CPP_CSVMANAGER_H
