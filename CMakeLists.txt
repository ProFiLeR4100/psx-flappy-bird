cmake_minimum_required(VERSION 3.6)
project(untitled)

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
execute_process(
        COMMAND echo  "test1"
        COMMAND touch "test1"
        COMMAND sleep 4s
        COMMAND echo  "test2"
        COMMAND touch "test2"
        COMMAND sleep 4s
        COMMAND echo  "test4"
)



#CHEARS!