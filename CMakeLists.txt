cmake_minimum_required(VERSION 3.15)

# Enable C++11
set(CMAKE_CXX_STANDARD 17)

# PROJECT_NAME=flv-parser
set(PROJECT_NAME flv-parser)
project(${PROJECT_NAME} LANGUAGES C CXX)
# set(PROJECT_NAME )
# set the project name
project(${PROJECT_NAME})

set(SRC 
    ${CMAKE_SOURCE_DIR}/main/main.cpp 
    ${CMAKE_SOURCE_DIR}/util/amf.cpp
    ${CMAKE_SOURCE_DIR}/util/error.cpp
    ${CMAKE_SOURCE_DIR}/util/streambuf.cpp
    ${CMAKE_SOURCE_DIR}/flv/flvparser.cpp
)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add includ path
include_directories(${CMAKE_SOURCE_DIR}/main
                    ${CMAKE_SOURCE_DIR}/util
                    ${CMAKE_SOURCE_DIR}/flv
                    )

# add the executable
add_executable(${PROJECT_NAME} ${SRC})

