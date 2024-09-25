cmake_minimum_required(VERSION 3.22.1)

project(
    client
    VERSION 0.0.1
    LANGUAGES CXX
)

aux_source_directory(. Client_SRC)
aux_source_directory(./video Client_SRC)
aux_source_directory(./sound Client_SRC)
message("Client_SRC: ${Client_SRC}")

add_library(${PROJECT_NAME} STATIC ${Client_SRC})