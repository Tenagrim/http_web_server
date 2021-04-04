cmake_minimum_required(VERSION 3.17)
project(webserv)
set(CMAKE_CXX_STANDARD 98)

INCLUDE_DIRECTORIES(./webserv/interfaces ./webserv/)

add_executable(
        webserv
        ./webserv/ABody.cpp
        ./webserv/ABody.hpp
        ./webserv/ABuildPolicy.cpp
        ./webserv/ABuildPolicy.hpp
        ./webserv/BasicRequest.cpp
        ./webserv/BasicRequest.hpp
        ./webserv/BasicResponse.cpp
        ./webserv/BasicResponse.hpp
        ./webserv/Client.cpp
        ./webserv/Client.hpp
        ./webserv/ConfigParser.cpp
        ./webserv/ConfigParser.hpp
        ./webserv/defines.hpp
        ./webserv/Dispatcher.cpp
        ./webserv/Dispatcher.hpp
        ./webserv/DispatcherEventArgs.hpp
        ./webserv/ErrorPager.cpp
        ./webserv/ErrorPager.hpp
#        ./webserv/FakeFakeRequestValidator.cpp
#        ./webserv/FakeFakeRequestValidator.hpp
#        ./webserv/FakeRequestValidator.cpp
#        ./webserv/FakeRequestValidator.hpp
        ./webserv/FakeTimeMachine.cpp
        ./webserv/FakeTimeMachine.hpp
        ./webserv/FileBody.cpp
        ./webserv/FileBody.hpp
        ./webserv/FileManager.cpp
        ./webserv/FileManager.hpp
        ./webserv/GetBuildPolicy.cpp
        ./webserv/GetBuildPolicy.hpp
        ./webserv/Header.cpp
        ./webserv/Header.hpp
        ./webserv/interfaces/IBody.hpp
        ./webserv/interfaces/ICgiController.hpp
        ./webserv/interfaces/IClient.hpp
        ./webserv/interfaces/IFileManager.hpp
        ./webserv/interfaces/IHeader.hpp
        ./webserv/interfaces/ILogger.hpp
        ./webserv/interfaces/ILoggerEvent.hpp
        ./webserv/interfaces/IRequest.hpp
        ./webserv/interfaces/IRequestReciever.hpp
        ./webserv/interfaces/IRequestValidator.hpp
        ./webserv/interfaces/IResponse.hpp
        ./webserv/interfaces/IResponseBuilder.hpp
        ./webserv/interfaces/IResponseSender.hpp
        ./webserv/interfaces/IServer.hpp
        ./webserv/interfaces/ITimeMachine.hpp
        ./webserv/LocationInit.cpp
        ./webserv/LocationInit.hpp
        ./webserv/main.cpp
        ./webserv/OutOperators.cpp
        ./webserv/PostBuildPolicy.cpp
        ./webserv/PostBuildPolicy.hpp
        ./webserv/PutBuildPolicy.cpp
        ./webserv/PutBuildPolicy.hpp
        ./webserv/Request.cpp
        ./webserv/Request.hpp
        webserv/RequestReceiver.cpp
        webserv/RequestReceiver.hpp
        ./webserv/ResponseBuilder.cpp
        ./webserv/ResponseBuilder.hpp
        ./webserv/ResponseSender.cpp
        ./webserv/ResponseSender.hpp
        ./webserv/runtime_error.cpp
        ./webserv/runtime_error.hpp
        ./webserv/Server.cpp
        ./webserv/Server.hpp
        ./webserv/ServerInit.cpp
        ./webserv/ServerInit.hpp
        ./webserv/TextBody.cpp
        ./webserv/TextBody.hpp
        ./webserv/TextResponse.cpp
        ./webserv/TextResponse.hpp
        ./webserv/TokenPool.cpp
        ./webserv/TokenPool.hpp
#        ./webserv/trash/reader.cpp
#        ./webserv/trash/unitTester.cpp
        ./webserv/utils/ft_memcpy.cpp
        ./webserv/utils/ft_strlen.cpp
        ./webserv/utils/getCodeDescr.cpp
        ./webserv/utils/getFileExtension.cpp
        ./webserv/utils/getHeaderKey.cpp
        ./webserv/utils/getMethod.cpp
        ./webserv/utils/to_string.cpp
        ./webserv/utils/Utils.cpp
        ./webserv/Utils.hpp
        ./webserv/webserv.hpp
      webserv/BodyReader.cpp webserv/BodyReader.hpp
        webserv/utils/isNumber.cpp webserv/HeaderMaker.cpp webserv/HeaderMaker.hpp webserv/utils/strToLower.cpp)
