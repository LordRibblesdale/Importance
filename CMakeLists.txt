cmake_minimum_required(VERSION 3.15)
project(CotecchioGame)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE VectorFolder "Vector/*.cpp" "Vector/*.h")
file(GLOB_RECURSE MatrixFolder "Matrix/*.cpp" "Matrix/*.h")
file(GLOB_RECURSE UtilitiesFolder "Utilities/*.cpp" "Utilities/*.h")
file(GLOB_RECURSE ExceptionFolder "Exception/*.h")
file(GLOB_RECURSE MainFile "Main.cpp")

file(GLOB_RECURSE GladLibraries "Graphics/glad/*.h" "Graphics/glad/*.c")
file(GLOB_RECURSE GLFWLibraries "Graphics/glfw-3.3.2.bin.WIN64/include/GLFW")

add_executable(${PROJECT_NAME}
        ${VectorFolder}
        ${MatrixFolder}
        ${ExceptionFolder}
        ${UtilitiesFolder}
        ${GladLibraries}
        ${GLFWLibraries}
        ${MainFile})

target_include_directories(${PROJECT_NAME} PRIVATE "Graphics/glad/include/glad")
target_include_directories(${PROJECT_NAME} PRIVATE "Graphics/glad/include/KHR")
target_include_directories(${PROJECT_NAME} PRIVATE "Graphics/glfw-3.3.2.bin.WIN64/include/GLFW")

target_link_libraries(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/Graphics/glfw-3.3.2.bin.WIN64/lib-mingw-w64/libglfw3.a")