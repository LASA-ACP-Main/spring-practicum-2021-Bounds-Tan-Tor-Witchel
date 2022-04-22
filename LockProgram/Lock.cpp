
#include "Lock.h"

bool Lock::getState(){
    return open;
}
void Lock::openLock(){
    open = true;
    system("python3 \"../Python Scripts/open.py\"");
}
void Lock::closeLock(){
    open = false;
    system("python3 \"../Python Scripts/close.py\"");
}

Lock::Lock(){
    open = false;
}

void Lock::shutdown(){
    closeLock();
}