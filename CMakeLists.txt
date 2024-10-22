cmake_minimum_required(VERSION 3.10)

# Project Name
project(SmartAssistant)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the whisper.cpp project
add_subdirectory(whisper.cpp)

# Add source files
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/main.cpp)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/whisper.cpp/include)
include_directories(${CMAKE_SOURCE_DIR}/whisper.cpp/ggml/include)

# Add the executable
add_executable(SmartAssistant ${SOURCES})

# Link libraries
target_link_libraries(SmartAssistant PUBLIC whisper common common-sdl ${CMAKE_THREAD_LIBS_INIT})