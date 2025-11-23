cmake_minimum_required(VERSION 3.20)
project(KruskalXPrim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-static)
add_link_options(-static)

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

# Only build tests in Debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
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
endif()
