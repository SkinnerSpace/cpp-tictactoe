cmake_minimum_required(VERSION 3.20)

project(TcpDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BOOST_ROOT "C:/Library/boost_1_91_0")

find_package(Boost REQUIRED)

add_executable(TcpServer
    Server/main.cpp
)

add_executable(TcpClient
    Client/main.cpp
)

target_include_directories(TcpServer PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(TcpClient PRIVATE ${Boost_INCLUDE_DIRS})

target_compile_definitions(TcpServer PRIVATE BOOST_ERROR_CODE_HEADER_ONLY)
target_compile_definitions(TcpClient PRIVATE BOOST_ERROR_CODE_HEADER_ONLY)

add_custom_command(
    TARGET TcpServer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/Server/server.conf"
        "$<TARGET_FILE_DIR:TcpServer>/server.conf"
)

add_custom_command(
    TARGET TcpClient POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/Client/client.conf"
        "$<TARGET_FILE_DIR:TcpClient>/client.conf"
)
