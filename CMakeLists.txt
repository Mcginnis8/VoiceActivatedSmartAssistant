cmake_minimum_required(VERSION 3.10)

# Project Name
project(SmartAssistant)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the whisper.cpp project
add_subdirectory(whisper.cpp)
add_subdirectory(SFML)

# Include directories for SFML
include_directories(${PROJECT_SOURCE_DIR}/../SFML/include)


# Link directories for SFML
link_directories(${PROJECT_SOURCE_DIR}/../SFML/lib)

link_directories(/opt/homebrew/lib)

# Add source files
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/listener.cpp ${PROJECT_SOURCE_DIR}/functionality.cpp)

# Add the executable
add_executable(SmartAssistant ${SOURCES})

# Link the executable to the SFML libraries
target_link_libraries(SmartAssistant PUBLIC sfml-graphics sfml-system sfml-window)

# Link libraries
target_link_libraries(SmartAssistant PUBLIC whisper)