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
CMAKE_SOURCE_DIR = /Users/ramneeksingh/Desktop/projects/genome-assembly-de-brujin-graph

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ramneeksingh/Desktop/projects/genome-assembly-de-brujin-graph/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/eulerian-path.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/eulerian-path.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/eulerian-path.dir/flags.make

CMakeFiles/eulerian-path.dir/eulerian-path.cpp.o: CMakeFiles/eulerian-path.dir/flags.make
CMakeFiles/eulerian-path.dir/eulerian-path.cpp.o: ../eulerian-path.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ramneeksingh/Desktop/projects/genome-assembly-de-brujin-graph/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/eulerian-path.dir/eulerian-path.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/eulerian-path.dir/eulerian-path.cpp.o -c /Users/ramneeksingh/Desktop/projects/genome-assembly-de-brujin-graph/eulerian-path.cpp

CMakeFiles/eulerian-path.dir/eulerian-path.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/eulerian-path.dir/eulerian-path.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ramneeksingh/Desktop/projects/genome-assembly-de-brujin-graph/eulerian-path.cpp > CMakeFiles/eulerian-path.dir/eulerian-path.cpp.i

CMakeFiles/eulerian-path.dir/eulerian-path.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/eulerian-path.dir/eulerian-path.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ramneeksingh/Desktop/projects/genome-assembly-de-brujin-graph/eulerian-path.cpp -o CMakeFiles/eulerian-path.dir/eulerian-path.cpp.s

# Object files for target eulerian-path
eulerian__path_OBJECTS = \
"CMakeFiles/eulerian-path.dir/eulerian-path.cpp.o"

# External object files for target eulerian-path
eulerian__path_EXTERNAL_OBJECTS =

eulerian-path: CMakeFiles/eulerian-path.dir/eulerian-path.cpp.o
eulerian-path: CMakeFiles/eulerian-path.dir/build.make
eulerian-path: CMakeFiles/eulerian-path.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ramneeksingh/Desktop/projects/genome-assembly-de-brujin-graph/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable eulerian-path"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eulerian-path.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/eulerian-path.dir/build: eulerian-path

.PHONY : CMakeFiles/eulerian-path.dir/build

CMakeFiles/eulerian-path.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/eulerian-path.dir/cmake_clean.cmake
.PHONY : CMakeFiles/eulerian-path.dir/clean

CMakeFiles/eulerian-path.dir/depend:
	cd /Users/ramneeksingh/Desktop/projects/genome-assembly-de-brujin-graph/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ramneeksingh/Desktop/projects/genome-assembly-de-brujin-graph /Users/ramneeksingh/Desktop/projects/genome-assembly-de-brujin-graph /Users/ramneeksingh/Desktop/projects/genome-assembly-de-brujin-graph/cmake-build-debug /Users/ramneeksingh/Desktop/projects/genome-assembly-de-brujin-graph/cmake-build-debug /Users/ramneeksingh/Desktop/projects/genome-assembly-de-brujin-graph/cmake-build-debug/CMakeFiles/eulerian-path.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/eulerian-path.dir/depend
