cmake_minimum_required(VERSION 3.15)
project(CotecchioGame)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE VectorFolder "Vector/*.cpp" "Vector/*.h")
file(GLOB_RECURSE MatrixFolder "Matrix/*.cpp" "Matrix/*.h")
file(GLOB_RECURSE ExceptionFolder "Exception/*.h")
file(GLOB_RECURSE MainFile "Main.cpp")

add_executable(${PROJECT_NAME}
        ${VectorFolder}
        ${MatrixFolder}
        ${ExceptionFolder}
        ${MainFile})