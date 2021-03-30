cmake_minimum_required(VERSION 3.17)
project(webserv)
set(CMAKE_CXX_STANDARD 98)
INCLUDE_DIRECTORIES(./webserv/interfaces ./webserv/)
#add_executable(
#        webserv
#        webserv/webserv.hpp
#        webserv/main.cpp
#        webserv/trash/unitTester.cpp
#        webserv/Request.cpp
#        webserv/Server.cpp
#        webserv/ConfigParser.cpp
#        webserv/ConfigParser.hpp
#        webserv/interfaces/IBody.hpp
#        webserv/interfaces/ICgiController.hpp
#        webserv/interfaces/IConfigParser.hpp
#        webserv/interfaces/IConfigValidator.hpp
#
#set(CMAKE_CXX_STANDARD 98)
#
#INCLUDE_DIRECTORIES(./webserv/interfaces)

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
        webserv/interfaces/IClient.hpp
        webserv/interfaces/IResponseBuilder.hpp
        webserv/interfaces/IResponseSender.hpp
        webserv/interfaces/IRequestReciever.hpp
        webserv/RequestReciever.hpp
        webserv/RequestReciever.cpp
        webserv/OutOperators.cpp
        webserv/interfaces/IRequest.hpp
        webserv/interfaces/IRequestValidator.hpp
        webserv/interfaces/IResponse.hpp
        webserv/interfaces/IServer.hpp
        webserv/interfaces/ITimeMachine.hpp
        webserv/Client.cpp
        webserv/Client.hpp
        webserv/Dispatcher.cpp
        webserv/Dispatcher.hpp
        webserv/FileManager.hpp
        webserv/FileManager.cpp
        webserv/ResponseBuilder.cpp
        webserv/ResponseBuilder.hpp
        webserv/utils/ft_memcpy.cpp
        webserv/trash/unitTester.cpp


        webserv/ConfigParser.cpp
        webserv/ConfigParser.hpp
        webserv/ServerInit.cpp
        webserv/ServerInit.hpp
        webserv/TokenPool.cpp
        webserv/TokenPool.hpp
        webserv/LocationInit.cpp webserv/LocationInit.hpp webserv/Utils.hpp webserv/utils/Utils.cpp)