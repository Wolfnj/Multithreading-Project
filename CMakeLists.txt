cmake_minimum_required(VERSION 3.13)
project(WolfNathanHW6)

set(CMAKE_CXX_STANDARD 11)

add_executable(WolfNathanHW6 main.cpp Knight.cpp Knight.h Log.cpp Log.h Rabbit.cpp Rabbit.h SafeQueue.cpp SafeQueue.h)

TARGET_LINK_LIBRARIES( WolfNathanHW6 pthread)