//
// Created by gideo on 3/31/2022.
//

#include "Lock.h"

bool getState(){
    return open;
}
bool openLock(){
    open = true;
}
bool closeLock(){
    open = false;
}