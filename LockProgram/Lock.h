#include <cstdio>
#include <unistd.h>
extern "C" {
#include <wiringPi.h>
}

#ifndef LOCKSIMULATION_LOCK_H
#define LOCKSIMULATION_LOCK_H
class Lock {
private:
    bool open;
public:
    Lock();

    bool getState();

    void openLock();

    void closeLock();

    void shutdown();
};

#endif //LOCKSIMULATION_LOCK_H
