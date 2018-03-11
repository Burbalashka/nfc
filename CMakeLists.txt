cmake_minimum_required(VERSION 3.9)
project(nfc C)

set(CMAKE_C_STANDARD 99)

add_executable(nfc Source/main.c Source/Ndef.c Source/Ndef.h Source/i2c_for_nfc.c Source/i2c_for_nfc.h)