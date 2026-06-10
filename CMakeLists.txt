cmake_minimum_required(VERSION 3.16)
project(cpp_p VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp_p 
src/main.cpp 
src/flags.cpp 
src/files.cpp
src/copy.cpp)
target_compile_options(cpp_p PRIVATE -Wall -Wextra -O2)
install(TARGETS cpp_p RUNTIME DESTINATION bin)

