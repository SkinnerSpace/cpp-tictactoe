cmake_minimum_required(VERSION 3.20)

project(TcpDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (WIN32)
    set(BOOST_ROOT "C:/Library/boost_1_91_0")
endif()

find_package(Boost REQUIRED COMPONENTS system)

add_executable(TcpServer
    Server/main.cpp
    Server/Server.cpp
    Server/ClientConnection.cpp
    Shared/PacketSerializer.cpp
)

add_executable(TcpClient
    Client/main.cpp
    Client/ClientConnection.cpp
    Shared/PacketSerializer.cpp
)

target_include_directories(TcpServer PRIVATE
    ${Boost_INCLUDE_DIRS}
    Server
    Shared
)

target_include_directories(TcpClient PRIVATE
    ${Boost_INCLUDE_DIRS}
    Client
    Shared
)

target_link_libraries(TcpServer PRIVATE
    Boost::system
)

target_link_libraries(TcpClient PRIVATE
    Boost::system
)
