cmake_minimum_required(VERSION 3.20)

project(webServer)

# execute_process(COMMAND find . -name "*.cpp" ! -path "./build/*" ! -path "./test_pressure/*" WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} RESULT_VARIABLE res OUTPUT_VARIABLE SRCS)

# message(STATUS ${res} ${SRCS})

# if(${res})
# message(FATAL_ERROR "find source file error")
# endif()
set(CMAKE_BUILD_TYPE "Debug")
set(SRCS
    ./src/http/http_conn.cpp
    ./src/webserver.cpp
    ./src/config/config.cpp
    ./src/mysql/sql_connection_pool.cpp
    ./src/main.cpp
    ./src/utils/utils.cpp
    ./src/log/log.cpp
)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} pthread mysqlclient)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)
