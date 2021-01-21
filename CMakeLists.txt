cmake_minimum_required(VERSION 3.17)
project(AlgoritemImplementation)

set(CMAKE_CXX_STANDARD 14)

add_executable(AlgoritemImplementation main.cpp Hash/Hash_Base.h Hash/Hash_Simple.h Hash/Hash.h Hash/Hash_Test.h)