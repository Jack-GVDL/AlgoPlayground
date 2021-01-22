cmake_minimum_required(VERSION 3.17)
project(AlgoritemImplementation)

set(CMAKE_CXX_STANDARD 14)

include_directories(Utility)

add_executable(AlgoritemImplementation main.cpp Map/UnorderedMap.h Map/UnorderedMap_Simple.h Map/Map.h Map/Hash_Test.h Utility/Pair.h Utility/Utility.h Map/UnorderedMap_Dynamic.h Utility/Bool.h)