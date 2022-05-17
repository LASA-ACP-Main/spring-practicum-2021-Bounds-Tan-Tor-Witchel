
#include "Lock.h"

bool Lock::getState(){
    return open;
}
void Lock::openLock(){
    open = true;
    
    Camera.grab();
    //allocate memory
    unsigned char *data=new unsigned char[  Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB )];
    //extract the image in rgb format
    Camera.retrieve ( data,raspicam::RASPICAM_FORMAT_RGB );
    //save
    std::ofstream outFile ( "photos/Lock_Opened_At_"+std::to_string(std::time(nullptr))+".ppm",std::ios::binary );
    outFile<<"P6\n"<<Camera.getWidth() <<" "<<Camera.getHeight() <<" 255\n";
    outFile.write ( ( char* ) data, Camera.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
    std::cout<<"Image saved"<<std::endl;
    //free resrources    
    delete data;
    
    pinMode(24, OUTPUT);
    digitalWrite(24, LOW);
    delay(100);
}
void Lock::closeLock(){
    open = false;
    pinMode(24, INPUT);
}

Lock::Lock() {
    open = false;
    pinMode(24, INPUT);
    std::cout<<"Opening Camera..."<<std::endl;
    if ( !Camera.open()) {std::cerr<<"Error opening camera - please relaunch"<<std::endl;}
    //wait a while until camera stabilizes
    std::cout<<"Sleeping for 3 secs"<<std::endl;
    delay(3000);
}

void Lock::shutdown(){
    closeLock();
}
