# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ramneeksingh/Desktop/projects/de-bruijn-graph-on-random-reads-with-errors

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ramneeksingh/Desktop/projects/de-bruijn-graph-on-random-reads-with-errors/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tip-removal.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tip-removal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tip-removal.dir/flags.make

CMakeFiles/tip-removal.dir/tip-removal.cpp.o: CMakeFiles/tip-removal.dir/flags.make
CMakeFiles/tip-removal.dir/tip-removal.cpp.o: ../tip-removal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ramneeksingh/Desktop/projects/de-bruijn-graph-on-random-reads-with-errors/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tip-removal.dir/tip-removal.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tip-removal.dir/tip-removal.cpp.o -c /Users/ramneeksingh/Desktop/projects/de-bruijn-graph-on-random-reads-with-errors/tip-removal.cpp

CMakeFiles/tip-removal.dir/tip-removal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tip-removal.dir/tip-removal.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ramneeksingh/Desktop/projects/de-bruijn-graph-on-random-reads-with-errors/tip-removal.cpp > CMakeFiles/tip-removal.dir/tip-removal.cpp.i

CMakeFiles/tip-removal.dir/tip-removal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tip-removal.dir/tip-removal.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ramneeksingh/Desktop/projects/de-bruijn-graph-on-random-reads-with-errors/tip-removal.cpp -o CMakeFiles/tip-removal.dir/tip-removal.cpp.s

# Object files for target tip-removal
tip__removal_OBJECTS = \
"CMakeFiles/tip-removal.dir/tip-removal.cpp.o"

# External object files for target tip-removal
tip__removal_EXTERNAL_OBJECTS =

tip-removal: CMakeFiles/tip-removal.dir/tip-removal.cpp.o
tip-removal: CMakeFiles/tip-removal.dir/build.make
tip-removal: CMakeFiles/tip-removal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ramneeksingh/Desktop/projects/de-bruijn-graph-on-random-reads-with-errors/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tip-removal"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tip-removal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tip-removal.dir/build: tip-removal

.PHONY : CMakeFiles/tip-removal.dir/build

CMakeFiles/tip-removal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tip-removal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tip-removal.dir/clean

CMakeFiles/tip-removal.dir/depend:
	cd /Users/ramneeksingh/Desktop/projects/de-bruijn-graph-on-random-reads-with-errors/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ramneeksingh/Desktop/projects/de-bruijn-graph-on-random-reads-with-errors /Users/ramneeksingh/Desktop/projects/de-bruijn-graph-on-random-reads-with-errors /Users/ramneeksingh/Desktop/projects/de-bruijn-graph-on-random-reads-with-errors/cmake-build-debug /Users/ramneeksingh/Desktop/projects/de-bruijn-graph-on-random-reads-with-errors/cmake-build-debug /Users/ramneeksingh/Desktop/projects/de-bruijn-graph-on-random-reads-with-errors/cmake-build-debug/CMakeFiles/tip-removal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tip-removal.dir/depend

