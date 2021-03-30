cmake_minimum_required(VERSION 3.17)
project(webserv)

set(CMAKE_CXX_STANDARD 98)

INCLUDE_DIRECTORIES(./webserv/interfaces)

add_executable(
        webserv
        webserv/main.cpp
        webserv/Request.cpp
        webserv/Server.cpp
        webserv/ConfigParser.cpp
        webserv/ConfigParser.hpp
        webserv/interfaces/IBody.hpp
        webserv/interfaces/ICgiController.hpp
        webserv/interfaces/IFileManager.hpp
        webserv/interfaces/IHeader.hpp
        webserv/interfaces/ILogger.hpp
        webserv/interfaces/ILoggerEvent.hpp
        webserv/interfaces/IRequest.hpp
        webserv/interfaces/IRequestValidator.hpp
        webserv/interfaces/IResponse.hpp
        webserv/interfaces/IServer.hpp
        webserv/interfaces/ITimeMachine.hpp

        webserv/ConfigParser.cpp
        webserv/ConfigParser.hpp
        webserv/ServerInit.cpp
        webserv/ServerInit.hpp
        webserv/Utils.cpp webserv/Utils.hpp
        webserv/interfaces/IUtils.hpp)