# stop if cmake version below 2.8
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# project name
project(heinz_sandbox)

# enable c
enable_language(C)

# project version
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")

set(CMAKE_BUILD_TYPE Release)
# Options. Turn on with 'cmake -Dtest=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.

################# SOLDRIVER LIB #######################################################################################

# include for solcient messagging APIs
include_directories(include)

# sources for the driver
file(GLOB SOURCES "src/*.c" "include/*.h")

# build a shared library
add_library(testlib SHARED ${SOURCES})

# OS agnositic preprocessor macros
add_definitions(-DPROVIDE_LOG_UTILITIES -DSOLCLIENT_EXCLUDE_DEPRECATED  -DSOLCLIENT_CONST_PROPERTIES)

# if OSX (Mac)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    SET(OperatingSystem "Mac OS X")
#    add_definitions(-DDARWIN_OS)
#    find_library(LIBSOLCLIENT_LIB
#            NAMES libsolclient.dylib
#            HINTS "solclient/lib/osx"
#            )
    add_custom_target(copyDependencies ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/lib/osx ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/output)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# if Linux
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux specific code
#    SET(OperatingSystem "Linux")
#    find_library(LIBSOLCLIENT_LIB
#            NAMES libsolclient.so
#            HINTS "solclient/lib/linux64"
#            )
#    target_link_libraries(soldriverc ${UUID_LIB})
    add_custom_target(copyDependencies ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/lib/linux64 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/output)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# link the driver to libsolclient
#target_link_libraries(soldriverc ${LIBSOLCLIENT_LIB})
set_target_properties(testlib PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY output/)

# copy the content of libsolclient libs to output for convenience
#add_dependencies(soldriverc copyDependencies)

################# Test Driver #########################################################################################
# sources for the driver
file(GLOB SOURCES_TEST "test/*.c" "test/*.h")
add_executable(testdriver ${SOURCES_TEST})
target_link_libraries(testdriver testlib)
set_target_properties(testdriver PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG output/
        RUNTIME_OUTPUT_DIRECTORY_RELEASE output/)


################# CTest ###############################################################################################
