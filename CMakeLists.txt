cmake_minimum_required(VERSION 4.0)
project(KruskalXPrim)

set(CMAKE_CXX_STANDARD 23)

set(core-files
        Graph.cpp
        Graph.hpp
        UnionFind.cpp
        UnionFind.hpp
        MST.hpp
        MST.cpp
)

add_executable(kxp
        main.cpp
        ${core-files}
)

add_executable(UnionFindTest
        tests/catch.hpp
        tests/catch.cpp
        tests/UnionFindTest.cpp
        ${core-files}
)

add_executable(GraphTest
        tests/catch.hpp
        tests/catch.cpp
        tests/GraphTest.cpp
        ${core-files}
)
add_executable(MSTTest
        tests/catch.hpp
        tests/catch.cpp
        tests/MSTTest.cpp
        ${core-files}
)

enable_testing()
add_test(NAME MSTTest COMMAND MSTTest)
add_test(NAME UnionFindTest COMMAND UnionFindTest)
add_test(NAME GraphTest COMMAND GraphTest)
