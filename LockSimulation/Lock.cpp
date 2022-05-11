
#include "Lock.h"

bool Lock::getState(){
    return open;
}
void Lock::openLock(){
    open = true;
}
void Lock::closeLock(){
    open = false;
}

Lock::Lock(){
    open = false;
}

void Lock::shutdown(){
    closeLock();
}
