# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/build

# Include any dependencies generated for this target.
include whisper.cpp/examples/bench/CMakeFiles/bench.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include whisper.cpp/examples/bench/CMakeFiles/bench.dir/compiler_depend.make

# Include the progress variables for this target.
include whisper.cpp/examples/bench/CMakeFiles/bench.dir/progress.make

# Include the compile flags for this target's objects.
include whisper.cpp/examples/bench/CMakeFiles/bench.dir/flags.make

whisper.cpp/examples/bench/CMakeFiles/bench.dir/bench.cpp.o: whisper.cpp/examples/bench/CMakeFiles/bench.dir/flags.make
whisper.cpp/examples/bench/CMakeFiles/bench.dir/bench.cpp.o: ../whisper.cpp/examples/bench/bench.cpp
whisper.cpp/examples/bench/CMakeFiles/bench.dir/bench.cpp.o: whisper.cpp/examples/bench/CMakeFiles/bench.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object whisper.cpp/examples/bench/CMakeFiles/bench.dir/bench.cpp.o"
	cd /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/build/whisper.cpp/examples/bench && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT whisper.cpp/examples/bench/CMakeFiles/bench.dir/bench.cpp.o -MF CMakeFiles/bench.dir/bench.cpp.o.d -o CMakeFiles/bench.dir/bench.cpp.o -c /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/whisper.cpp/examples/bench/bench.cpp

whisper.cpp/examples/bench/CMakeFiles/bench.dir/bench.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bench.dir/bench.cpp.i"
	cd /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/build/whisper.cpp/examples/bench && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/whisper.cpp/examples/bench/bench.cpp > CMakeFiles/bench.dir/bench.cpp.i

whisper.cpp/examples/bench/CMakeFiles/bench.dir/bench.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bench.dir/bench.cpp.s"
	cd /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/build/whisper.cpp/examples/bench && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/whisper.cpp/examples/bench/bench.cpp -o CMakeFiles/bench.dir/bench.cpp.s

# Object files for target bench
bench_OBJECTS = \
"CMakeFiles/bench.dir/bench.cpp.o"

# External object files for target bench
bench_EXTERNAL_OBJECTS =

bin/bench: whisper.cpp/examples/bench/CMakeFiles/bench.dir/bench.cpp.o
bin/bench: whisper.cpp/examples/bench/CMakeFiles/bench.dir/build.make
bin/bench: whisper.cpp/src/libwhisper.so.1.7.1
bin/bench: whisper.cpp/ggml/src/libggml.so
bin/bench: whisper.cpp/examples/bench/CMakeFiles/bench.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/bench"
	cd /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/build/whisper.cpp/examples/bench && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bench.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
whisper.cpp/examples/bench/CMakeFiles/bench.dir/build: bin/bench
.PHONY : whisper.cpp/examples/bench/CMakeFiles/bench.dir/build

whisper.cpp/examples/bench/CMakeFiles/bench.dir/clean:
	cd /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/build/whisper.cpp/examples/bench && $(CMAKE_COMMAND) -P CMakeFiles/bench.dir/cmake_clean.cmake
.PHONY : whisper.cpp/examples/bench/CMakeFiles/bench.dir/clean

whisper.cpp/examples/bench/CMakeFiles/bench.dir/depend:
	cd /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/whisper.cpp/examples/bench /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/build /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/build/whisper.cpp/examples/bench /mnt/c/Users/Cole/OneDrive/PreviousDocuments/ECE4122/VoiceActivatedSmartAssistant/build/whisper.cpp/examples/bench/CMakeFiles/bench.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : whisper.cpp/examples/bench/CMakeFiles/bench.dir/depend

