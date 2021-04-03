cmake_minimum_required(VERSION 3.17)
project(webserv)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED )
INCLUDE_DIRECTORIES(./webserv/interfaces ./webserv/)


aux_source_directory(webserv COM_DIR)
aux_source_directory(webserv/utils UTILS_DIR)
add_executable(
        webserv
        ${COM_DIR}
        ${UTILS_DIR}
        webserv/HeadBuildPolicy.cpp webserv/HeadBuildPolicy.hpp)
