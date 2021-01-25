cmake_minimum_required(VERSION 3.17)
project(AlgoritemImplementation)

set(CMAKE_CXX_STANDARD 14)

include_directories(Utility)

add_executable(
        AlgorithmImplementation
        main.cpp
        Map/UnorderedMap_Base.h
        Map/UnorderedMap_Simple.h
        Map/Map.h
        Map/Map_Test.h
        Utility/Pair.h
        Utility/Utility.h
        Map/UnorderedMap_Dynamic.h
        Utility/Bool.h
        List/List.h
        List/Vector.h
        List/List_Base.h
        List/List_Test.h
        List/Linked.h)