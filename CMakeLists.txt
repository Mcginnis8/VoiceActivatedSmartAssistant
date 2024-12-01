cmake_minimum_required(VERSION 3.10)

# Project Name
project(SmartAssistant)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the whisper.cpp project
add_subdirectory(whisper.cpp)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

# Find CURL
find_package(CURL REQUIRED)

# include_directories(${SFML_INCLUDE_DIR})

# Add source files
file(GLOB SOURCES 
    ${PROJECT_SOURCE_DIR}/main.cpp 
    ${PROJECT_SOURCE_DIR}/listener.cpp 
    ${PROJECT_SOURCE_DIR}/functionality.cpp 
    ${PROJECT_SOURCE_DIR}/jokes.txt
)

# Add the executable
add_executable(SmartAssistant ${SOURCES})

# Link SFML, CURL, and whisper libraries
target_link_libraries(SmartAssistant 
    PRIVATE 
        sfml-graphics 
        sfml-system 
        sfml-window 
        CURL::libcurl 
        whisper
)