project (maintest) 
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#---------------src--------------
set(TEST_DIR_SRCS   ./
                    ./common
                    ./common/ipc
                    ./common/queue
                    ./project
                    ./test 
)

set(TEST_DIR_SRCS   ${TEST_DIR_SRCS}
#[begin]
                    ./project/base
                    ./project/topic 
                    ./project/can
                    ./project/lin
                    ./project/common
                    ./project/fds
                    ./test/fds/chimeform
#[end]
)
#---------------include--------------
set(DIR_INCLUDE     ${TEST_DIR_SRCS}
                    ./common/doctest
                    ./include
)

set(CMAKE_BUILD_TYPE "Debug")
foreach(SOURCE_FILE ${TEST_DIR_SRCS})
    AUX_SOURCE_DIRECTORY(${SOURCE_FILE} DIR_SRCS)
endforeach()


include_directories(${DIR_INCLUDE})
add_executable(${PROJECT_NAME} ${DIR_SRCS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -pthread") 
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") #成代码覆盖率所必须的