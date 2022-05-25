cmake_minimum_required(VERSION 3.10)
project(RType VERSION 1.0)

### Set ###
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)
# set(SFML_STATIC_LIBRARIES TRUE)
set(THREADS_PREFER_PTHREAD_FLAG ON)

### CONAN ###
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
conan_basic_setup()

### FIND PACKAGES ###
find_package(asio REQUIRED)
find_package(SFML 2.5.1 COMPONENTS graphics audio network system window REQUIRED)
find_package(Threads REQUIRED)

### Windows ###
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_compile_options(/W4 /std:c++17)
endif()

### LINUX ###
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    add_definitions("-std=c++17 -D_GLIBCXX_USE_CXX11_ABI=0") # Flag to add on real ubuntu -D_GLIBCXX_USE_CXX11_ABI=0
    set(CMAKE_CXX_FLAGS "-Wextra -Wall")
endif(CMAKE_COMPILER_IS_GNUCXX)

### SOURCE FILES ###
file(GLOB_RECURSE SRC_SERVER RELATIVE ${CMAKE_SOURCE_DIR} "server/src/*.cpp")
file(GLOB_RECURSE SRC_CLIENT RELATIVE ${CMAKE_SOURCE_DIR} "client/src/*.cpp")
file(GLOB_RECURSE SRC_CLIENT_STATES RELATIVE ${CMAKE_SOURCE_DIR} "client/src/states/*.cpp")
file(GLOB_RECURSE SRC_CLIENT_STATES RELATIVE ${CMAKE_SOURCE_DIR} "client/src/ecs/generic/Component/*.cpp")
file(GLOB_RECURSE SRC_CLIENT_STATES RELATIVE ${CMAKE_SOURCE_DIR} "client/src/ecs/generic/Entity/*.cpp")
file(GLOB_RECURSE SRC_CLIENT_STATES RELATIVE ${CMAKE_SOURCE_DIR} "client/src/gui/*.cpp")
file(COPY "./client/assets" DESTINATION "./")
file(COPY "./client/configurations" DESTINATION "./")

### BINARIES ###
add_executable(
    r-type_server
    ${SRC_SERVER}
)
add_executable(
    r-type_client
    ${SRC_CLIENT}
)

### INCLUDES ###
include_directories(
    ${CONAN_INCLUDE_DIRECTORIES}
    ${PROJECT_SOURCE_DIR}/common/inc
    ${PROJECT_SOURCE_DIR}/common/inc/network
    ${CONAN_INCLUDE_DIRECTORIES}
)
target_include_directories(
    r-type_server PUBLIC
    ${PROJECT_SOURCE_DIR}/server/inc/
    ${PROJECT_SOURCE_DIR}/server/inc/generic/abstract/
    ${PROJECT_SOURCE_DIR}/server/inc/generic/abstract/client
    ${PROJECT_SOURCE_DIR}/server/inc/generic/abstract/server
    ${PROJECT_SOURCE_DIR}/server/inc/generic/asio
    ${PROJECT_SOURCE_DIR}/server/inc/generic/asio/client
    ${PROJECT_SOURCE_DIR}/server/inc/generic/asio/server
    ${PROJECT_SOURCE_DIR}/server/inc/generic/asio/socket
    ${PROJECT_SOURCE_DIR}/server/inc/specific
    ${CONAN_INCLUDE_DIRECTORIES}
)
target_include_directories(
    r-type_client PUBLIC
    ${PROJECT_SOURCE_DIR}/client/inc/
    ${PROJECT_SOURCE_DIR}/client/inc/states
    ${PROJECT_SOURCE_DIR}/client/inc/states/meta
    ${PROJECT_SOURCE_DIR}/client/inc/gui
    ${PROJECT_SOURCE_DIR}/client/inc/models
    ${PROJECT_SOURCE_DIR}/client/inc/network
    ${PROJECT_SOURCE_DIR}/client/inc/ecs/generic
    ${PROJECT_SOURCE_DIR}/client/inc/ecs/generic/Component
    ${PROJECT_SOURCE_DIR}/client/inc/ecs/generic/Entity
    ${PROJECT_SOURCE_DIR}/client/inc/ecs/generic/System
    ${CONAN_INCLUDE_DIRECTORIES}
)

### LINK ###
link_libraries(
    ${CONAN_LIBS}
)

target_link_libraries(
    r-type_server PRIVATE
    Threads::Threads
)
target_link_libraries(
    r-type_client PRIVATE
    sfml-graphics sfml-window sfml-system sfml-audio sfml-network
)