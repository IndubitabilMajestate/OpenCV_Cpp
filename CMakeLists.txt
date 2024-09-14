cmake_minimum_required(VERSION 3.10)

project(OPENCV_CPP)

set(CMAKE_CXX_STANDARD 17)
#if(NOT CMAKE_BUILD_TYPE)
#  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug Release" FORCE)
#endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug Release" FORCE)
endif()
message("${CMAKE_BUILD_TYPE}")
set(OpenCV_DIR C:/opencv/build)
find_package(OpenCV REQUIRED)
#message("${CMAKE_SOURCE_DIR}")

set(PROJ_ROOT "${CMAKE_SOURCE_DIR}/individual_proj")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug/individual_proj")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/individual_proj")

file(GLOB_RECURSE MAIN_FILES "${PROJ_ROOT}/*/main.cpp")
foreach(MAIN_FILE ${MAIN_FILES})
    #message("${MAIN_FILE}")
    get_filename_component(SUBFOLDER_NAME ${MAIN_FILE} DIRECTORY)
    message("This is SUBFOLDER_NAME_1: ${SUBFOLDER_NAME}")
    get_filename_component(SUBFOLDER_NAME ${SUBFOLDER_NAME} NAME)
    message("This is SUBFOLDER_NAME_2: ${SUBFOLDER_NAME}")
    #set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/individual_proj/${SUBFOLDER_NAME}")
    message("${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}")
    add_executable(${SUBFOLDER_NAME} ${MAIN_FILE})
    message(STATUS "Adding executable: ${SUBFOLDER_NAME} from ${MAIN_FILE} to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}")

    target_link_libraries(${SUBFOLDER_NAME} ${OpenCV_LIBS})
endforeach()
