cmake_minimum_required(VERSION 3.17)
project(AlgoritemImplementation)

set(CMAKE_CXX_STANDARD 14)

include_directories(Utility)
include_directories(List)
include_directories(Map)
include_directories(Queue)
include_directories(UnionTree)
include_directories(Test)
include_directories(Path)

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
        List/Linked.h Queue/Stack.h Queue/Queue_Base.h Queue/Queue.h Utility/Iterator.h UnionTree/UnionTree.h Utility/Algorithm.h Utility/Debug.h Map/OrderedMap_Base.h Map/OrderedMap_RBTree.h List/String.h Utility/Address.h Map/TreeNode.h List/Sort.h Utility/Random.h Test/Test.h Test/TestOperation.h Utility/Sort.h Utility/Select.h Path/Path.h Path/Path_ShortestPath.h)