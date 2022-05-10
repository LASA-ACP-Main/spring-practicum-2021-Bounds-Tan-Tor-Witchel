//g++ test.cpp MFRC522.cpp -lbcm2835 -lwiringPi

#include <iostream>
#include <string>
#include <cstdio>
#include <unistd.h>
#include "MFRC522.h"
extern "C" {
#include <wiringPi.h>
}

//wiringPi numbers, NOT BCM
#define L1 23
#define L2 25
#define L3 11
#define L4 31

#define C1 26
#define C2 27
#define C3 28
#define C4 29

//RFID Reset pin = 22
//RFID SCK Pin = 24 (I think, that may be SDA)

using namespace std;

void readLine(int line,string characters[4]){
    digitalWrite(line, 1);
    
	//for some reason, L4+C2 (character 0) also triggers L4+C1 (character *)
	//because of this, they are conditional in reverse order.
    if(digitalRead(C4) == 1){
        cout << (characters[3]) << endl;
        }
    else if(digitalRead(C3) == 1){
        cout << (characters[2]) << endl;
	}
    else if(digitalRead(C2) == 1){
        cout << (characters[1]) << endl;
	}
    else if(digitalRead(C1) == 1){
        cout << (characters[0]) << endl;
	}
    digitalWrite(line, 0);
}


int main(void){
	wiringPiSetup();
	cout << "Testing Lock" << endl;
	delay(1000);
	//open lock
	pinMode(24, OUTPUT);
	digitalWrite(24, LOW);
	delay(1000);

	//close lock
	pinMode(24, INPUT);
	
	//read keypad
	//init pins
	cout << "Reading Keypad and RIFD" << endl;
	 
	pinMode(L1, OUTPUT);
	pinMode(L2, OUTPUT);
	pinMode(L3, OUTPUT);
	pinMode(L4, OUTPUT);

	pinMode(C1, INPUT);
	pinMode(C2, INPUT);
	pinMode(C3, INPUT);
	pinMode(C4, INPUT);

	pullUpDnControl(C1,  PUD_DOWN);
	pullUpDnControl(C2,  PUD_DOWN);
	pullUpDnControl(C3,  PUD_DOWN);
	pullUpDnControl(C4,  PUD_DOWN);
	
	MFRC522 rfid;
	rfid.PCD_Init();
	string UID;
	
	//read loop
	while(true){
		string line1[4] = {"1","2","3","A"};
		string line2[4] = {"4","5","6","B"};
		string line3[4] = {"7","8","9","C"};
		string line4[4] = {"*","0","#","D"};

		readLine(L1, line1);
		readLine(L2, line2);
		readLine(L3, line3);
		readLine(L4, line4);
		delay(100);
		
		// Look for a card
		if(!rfid.PICC_IsNewCardPresent()){}

		else if( !rfid.PICC_ReadCardSerial()){}
		
		else{
		UID = "";
		// Print UID
		for(byte i = 0; i < rfid.uid.size; ++i){
			if(rfid.uid.uidByte[i] < 0x10){
				UID+=" 0";
				UID+= to_string(rfid.uid.uidByte[i]);
			}
			else{
				UID+= " ";
				UID+= to_string(rfid.uid.uidByte[i]);
			}
		}
		cout << UID << "\n";
		delay(500);
		}
	}
	return 0;
}
