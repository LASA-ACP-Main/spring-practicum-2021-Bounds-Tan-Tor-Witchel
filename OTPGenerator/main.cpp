#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <windows.h>

int main() {
    //read secret from file
    std::string secret;
    //this filepath has to be ../ for clion or normal for everything else
    std::ifstream myFile("../OTPSecret.txt");
    if(myFile.is_open()){
        getline(myFile, secret);
    }
    else{
        std::cout << "Failed to read OTP from file" << std::endl;
    }
    myFile.close();

    //generate code
    long long time = std::time(nullptr);
    time = floor(time/30);
    std::string shortTime =  std::to_string(time);
    std::string key = secret+shortTime;
    std::hash<std::string> str_hash;
    key = "000000"+std::to_string(str_hash(key));
    key = key.substr(key.length()-6, key.length());

    //output code
    std::cout << key;
    //copy to clipboard (this code may be dangerous)
    const char* output = &key[0];
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    //if we want to add file outputs here later, we can

    return 0;
}
