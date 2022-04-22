#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <string>
#include <vector>

#define pathToRfidInput "../rfidIn.txt"
#define pathToNumpadInput "../numpadIn.txt"
#define pathToManagementInput "../managementIn.txt"


bool isNum(std::string s){
    if(s == "0" || s == "1" || s == "2" || s == "3" || s == "4" || s == "5" || s == "6" || s == "7" ||
       s == "8" || s == "9"){
        return true;
    }
    return false;
}

bool isNum(char s){
    if(s == '0'  || s == '1' ||  s == '2' ||  s == '3' || s == '4'  || s == '5' || s == '6' || s == '7' ||
       s == '8' || s == '9'){
        return true;
    }
    return false;
}

bool isNumLong(std::string s){
    for(int i = 0; i < s.length(); i++){
        if(!isNum(s[i])){
            return false;
        }
    }
    return true;
}

void getKeypadInput(){
    std::string keypadRaw = "";
    std::fstream keypadFile(pathToNumpadInput);
    if (keypadFile.is_open() && !keypadFile.eof())
    {
        //read and clear
        getline(keypadFile, keypadRaw);
    }
    else{
        std::cout << "failed to read keypadRaw from file" << std::endl;
    }
    keypadFile.close();

    std::ofstream clearing1(pathToNumpadInput);
    clearing1.close();

    if(keypadRaw.empty()){
        return;
    }
    for(char x : keypadRaw){
        if(x == '#'){
            std::cout << "added to Keypad " << (x) << std::endl;
            break;
        }

        if (!isNum(x)) {
            std::cout << "Invalid Keypad Input" << std::endl;
        }
        else {
            std::cout << "added to Keypad " << (x) << std::endl;
        }
    }
}

void getRfidInput(){
    std::string rfidRaw = "";
    std::fstream rfidFile(pathToRfidInput);
    if (rfidFile.is_open() && !rfidFile.eof())
    {
        //read and clear
        getline(rfidFile, rfidRaw);
    }
    else{
        std::cout << "failed to read rfidRaw from file" << std::endl;
    }
    rfidFile.close();

    std::ofstream clearing2(pathToRfidInput);
    clearing2.close();

    if(rfidRaw.empty()){
        return;
    }
    if(rfidRaw.length() != 6 || !isNumLong(rfidRaw)){
        std::cout << "Invalid Input" << std::endl;
    }
    else {
        std::cout << "added to RFID " << rfidRaw << std::endl;
    }
}

void checkManagementMode(bool* keepRunning){
    std::vector<std::string> managementRaw;
    std::string* temp;
    int counter = 0;
    std::fstream managementFile(pathToManagementInput);
    while (managementFile.is_open() && !managementFile.eof())
    {
        //read and clear
        temp = new std::string;
        getline(managementFile, *temp);
        managementRaw.push_back(*temp);
    }

    managementFile.close();

    std::ofstream clearing(pathToManagementInput);
    clearing.close();

    if(managementRaw.empty()){
        return;
    }
    std::vector<std::string> users;
    std::string toRemove = "";
    std::string toAdd;
    std::string secretToAdd;
    for(std::string x : managementRaw) {
        if (x != ""){
            //Input Loop
            int feature = stoi(x.substr(0, 1));
            switch (feature) {
                case 0:
                    std::cout << "Shutdown" << std::endl;
                    *keepRunning = false;
                    break;
                case 1:
                    toRemove = x.substr(1, x.length() - 1);
                    std::cout << "Removed from RFID Users " << toRemove << std::endl;
                    break;
                case 2:
                    toAdd = x.substr(1, x.length() - 1);
                    std::cout << "Added to RFID Users " << toAdd << std::endl;
                    break;
                case 3:
                    secretToAdd = x.substr(1, x.length() - 1);
                    std::cout << "Set OTP Secret to " << secretToAdd << std::endl;
                    break;
                default:
                    std::cout << "Invalid Input" << std::endl;
                    break;
            }
        }
    }
}

int main() {

    bool* keepRunning = new bool;
    *keepRunning = true;

    while(*keepRunning) {
        //Check to open the lock
        //Input Loop
        getRfidInput();
        getKeypadInput();
        checkManagementMode(keepRunning);

    }
    return 0;
}
