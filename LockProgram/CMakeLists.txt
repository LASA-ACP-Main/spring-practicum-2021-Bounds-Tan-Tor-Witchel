cmake_minimum_required(VERSION 3.22)
project(LockProgram)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LockProgram
        csvManager.cpp
        csvManager.h
        Keypad.cpp
        Keypad.h
        Lock.cpp
        Lock.h
        main.cpp
        Otp.cpp
        Otp.h
        Rfid.cpp
        Rfid.h
        SQueue.cpp
        SQueue.h)
