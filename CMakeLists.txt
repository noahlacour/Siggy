cmake_minimum_required(VERSION 3.16)
project(siggy)

find_package(AWSSDK REQUIRED COMPONENTS s3)

add_executable(siggy 
    src/main.cpp 
    src/config.cpp 
    src/aws_s3.cpp
)

target_include_directories(siggy PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(siggy ${AWSSDK_LINK_LIBRARIES} inih)