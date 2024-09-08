project (maintest) 
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#---------------src--------------
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)
AUX_SOURCE_DIRECTORY(./common DIR_SRCS)
AUX_SOURCE_DIRECTORY(./common/ipc DIR_SRCS)
AUX_SOURCE_DIRECTORY(./common/queue DIR_SRCS)

#---------------include--------------
set(DIR_INCLUDE ./include ./ ./common)

set(CMAKE_BUILD_TYPE "Debug")
include_directories(${DIR_INCLUDE})
add_executable(${PROJECT_NAME} ${DIR_SRCS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -pthread") 
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") #成代码覆盖率所必须的