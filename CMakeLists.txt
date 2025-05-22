cmake_minimum_required(VERSION 3.28)
project(jump-particles LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_subdirectory(jump-particles-1)
add_subdirectory(jump-particles-2)
add_subdirectory(jump-particles-3)
add_subdirectory(jump-particles-4)
add_subdirectory(jump-particles-5)
add_subdirectory(jump-particles-6)
add_subdirectory(jump-particles-7)
add_subdirectory(jump-particles-8)