#include <cstdio>
#include <unistd.h>
#include <raspicam/raspicam.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>
extern "C" {
#include <wiringPi.h>
}

#ifndef LOCKSIMULATION_LOCK_H
#define LOCKSIMULATION_LOCK_H
class Lock {
private:
    bool open;
    raspicam::RaspiCam Camera;
public:
    Lock();

    bool getState();

    void openLock();

    void closeLock();

    void shutdown();
};

#endif //LOCKSIMULATION_LOCK_H
