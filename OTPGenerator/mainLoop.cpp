
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>

int main() {
    //read secret from file
    std::string secret;
    //this filepath has to be ../ for clion or normal for everything else
    std::ifstream myFile("OTPSecret.txt");
    if(myFile.is_open()){
        getline(myFile, secret);
    }
    else{
        std::cout << "Failed to read OTP from file" << std::endl;
    }
    myFile.close();
    
    std::string key2 = "";
    
	while(true){
    //generate code
    long long time = std::time(nullptr);
    time = floor(time/30);
    std::string shortTime =  std::to_string(time);
    key2 = secret+shortTime;
    std::hash<std::string> str_hash;
    key2 = "000000"+std::to_string(str_hash(key2));
    key2 = key2.substr(key2.length()-6, key2.length());

	if(floor((std::time(nullptr)-1)/30) != floor((std::time(nullptr))/30)){
		std::cout << key2 << std::endl;
		}
	}

    return 0;
}
