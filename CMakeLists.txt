cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME sfml_app)
project(${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(BUILD_SHARED_LIBS OFF)

file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Entities/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GUI/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/States/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/System/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/World/*.cpp
)

# Download SFML files
include(FetchContent)
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FetchContent_MakeAvailable(SFML)

# Link SFML libraries
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)

install(TARGETS ${PROJECT_NAME})

# Include headers
target_include_directories(${PROJECT_NAME} PRIVATE "include")

# Copy resources to build folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})