
cmake_minimum_required(VERSION 3.22.0)

project(
    Plants_vs_Zombies
    VERSION 0.0.0
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

include(CTest)
enable_testing()

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

include_directories(./include)
include_directories(./include/client)
include_directories(./include/client/video)
include_directories(./include/client/sound)
# include_directories(./include/client/scene)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(ENV{CONDA_PREFIX} "C:/Users/13277/.conda/envs/game/Library")
message(STATUS "CURRENT CONDA PREFIX: $ENV{CONDA_PREFIX}")
include_directories($ENV{CONDA_PREFIX}/include)
link_directories($ENV{CONDA_PREFIX}/lib)

add_subdirectory(./src/client)
add_executable(${PROJECT_NAME} ./src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE client)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    SDL2main SDL2_test SDL2 SDL2_image SDL2_ttf SDL2_mixer
)