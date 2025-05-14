cmake_minimum_required(VERSION 3.10)
project(SDLTTFtest)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SDLTTFtest_SOURCE_DIR}/cmake")

message(${CMAKE_MODULE_PATH})

# Set an output directory for our binaries
set(BIN_DIR ${SDLTTFtest_SOURCE_DIR}/bin)

set (CMAKE_CXX_STANDARD 20)

# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++20 -lSDL3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")

# Look up SDL3 and SDL3_TTF
find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

# # If you don't want SDL_ttf, then remove this section.
# set(SDLTTF_VENDORED ON) # tell SDL_ttf to build its own dependencies
# add_subdirectory(SDL_ttf EXCLUDE_FROM_ALL)

include_directories(${SDL3_INCLUDE_DIR})
add_executable(app sdlttf_test.cpp)

target_link_libraries(app
    #SDL3_ttf::SDL3_ttf      # remove if you are not using SDL_ttf
    SDL3_ttf::SDL3_ttf
    SDL3::SDL3
)
install(TARGETS app RUNTIME DESTINATION ${BIN_DIR})
