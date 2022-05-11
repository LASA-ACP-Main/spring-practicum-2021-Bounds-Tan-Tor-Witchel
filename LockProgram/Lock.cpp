
#include "Lock.h"

bool Lock::getState(){
    return open;
}
void Lock::openLock(){
    open = true;
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
}

void Lock::shutdown(){
    closeLock();
}
