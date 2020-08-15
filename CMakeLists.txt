cmake_minimum_required(VERSION 3.6)
project(PSxFlappyBird VERSION 0.1)

set(CMAKE_CXX_STANDARD 98)

#Set your directories.  The dot representes the root application folder.
#Thus my the path to my domain folder:
set(HDRS ./include)
set(SOURCES ./src)
set(PSYQ_INCLUDES "C:\\Projects\\PSYQ_SDK\\psyq\\include")

#Include the directories and now your cpp files will recognize your headers
include_directories(${HDRS})
include_directories(${PSYQ_INCLUDES})

FILE(GLOB SOURCE_FILES ${SOURCES}/*.cpp)

add_executable(untitled ${SOURCE_FILES})

add_custom_target(
        PSxFlappyBird
        COMMAND psymake
)


#CHEARS!