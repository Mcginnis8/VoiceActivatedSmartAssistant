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

# Find PortAudio
find_package(PkgConfig REQUIRED)
pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)

# Include directories
include_directories(${PORTAUDIO_INCLUDE_DIRS})

# Add the executable
add_executable(SmartAssistant ${SOURCES})

# Link libraries
target_link_libraries(SmartAssistant PUBLIC ${PORTAUDIO_LIBRARIES})
target_link_libraries(SmartAssistant PUBLIC whisper)