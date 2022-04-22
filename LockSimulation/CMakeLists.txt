cmake_minimum_required(VERSION 3.21)
project(LockSimulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(LockSimulation main.cpp Lock.cpp Lock.h Rfid.cpp Rfid.h Keypad.cpp Keypad.h Otp.cpp Otp.h csvManager.cpp csvManager.h SQueue.cpp SQueue.h BSTree.cpp BSTree.h HashTable.cpp HashTable.h LinkedList.cpp LinkedList.h BSTree.cpp BSTree.h)
