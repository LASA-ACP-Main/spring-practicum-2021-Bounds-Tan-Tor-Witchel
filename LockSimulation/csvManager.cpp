
#include "csvManager.h"
using namespace std;

vector<string> parseLine(string str) {
    string currentWord = "";
    vector<string> parsedLine;
    for (auto x : str) {
        if (x && x != ',') {
            currentWord += x;
        }
        else {
            parsedLine.push_back(currentWord);
            currentWord = "";
        }
    }
    return parsedLine;
}

vector<vector<string>> parseCSV(ifstream myFile) {
    if (myFile.is_open()) {

        string line = "";
        vector<vector<string>> unInfo;

        while (!myFile.eof()) {

            getline(myFile, line);
            if (line.find(",") != string::npos) {
                unInfo.push_back(parseLine(line));
            }

        }

        myFile.close();
        return unInfo;
    }

    cout << "unable to open file";
    vector<vector<string>> blank;
    return (blank);
}

void print2dArray(vector<vector<string>> in) {
    for (auto x : in) {
        for (auto y : x) {
            cout << y << " ";
        }
        cout << endl;
    }
}

void output2dArray(vector<vector<string>> in, ofstream out){
    for (auto x : in) {
        for (auto y : x) {
            out << y << ",";
        }
        out << endl;
    }
    out.close();
}

vector<vector<string>> sort2dArray(vector<vector<string>> in, int col) {
    bool start = false;
    const int inSize= static_cast<int>(in.size());
    for (int i = 0; i < inSize; i++) {
        if (!start) {
            start = true;
            for (int j = 0; j < in[i].size(); j++) {
                if (in[i][j] == "") { start = false; }
            }
        }

        else {
            int min = i;
            for (int j = i; j < inSize; j++) {
                if (stoi(in[j][col]) < stoi(in[min][col])) {
                    min = j;
                }

                vector<string> temp = in[i];
                in[i] = in[min];
                in[min] = temp;
            }
        }
    }

    return in;
}

void printCol(vector<vector<string>> in, int col) {
    for (auto x : in) {
        if(x == in[in.size()-1]){
            cout << x[col];
        }
        else{
            cout << x[col] << ",";
        }
    }
    cout << endl;
}

void printCleanCol(vector<vector<string>> in, int col) {
    bool start = false;
    for (auto x : in) {
        if (!start) {
            start = true;
            for (auto j : x) {
                if (j == "") { start = false; }
            }
        }
        else{

            if(x == in[in.size()-1]){
                cout << x[col];
            }
            else{
                cout << x[col] << ", ";
            }
        }
    }
    cout << endl;
}

void printRow(vector<vector<string>> in, int row) {
    for (size_t i = 0; i < in[row].size(); i++) {
        cout << in[row][i] << ", ";
    }
    cout << endl;
}
