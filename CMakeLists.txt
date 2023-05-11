cmake_minimum_required(VERSION 3.15)
project(curl_test VERSION 1.0.0 LANGUAGES C)

if (APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum OS X deployment target")

    if (${CMAKE_BUILD_TYPE} MATCHES Release OR ${CMAKE_BUILD_TYPE} MATCHES MinSizeRel)
        set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
    endif()
endif()

include(IncludeCurl.cmake)

add_executable(app main.c)
target_link_libraries(app PRIVATE libcurl)
target_include_directories(app PUBLIC modules/curl/include)
