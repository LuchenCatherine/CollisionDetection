# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/catherine/Research/CollisionDetection/AABBTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/catherine/Research/CollisionDetection/AABBTest/build

# Include any dependencies generated for this target.
include CMakeFiles/boolean_operation.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/boolean_operation.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/boolean_operation.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/boolean_operation.dir/flags.make

CMakeFiles/boolean_operation.dir/boolean_operation.cpp.o: CMakeFiles/boolean_operation.dir/flags.make
CMakeFiles/boolean_operation.dir/boolean_operation.cpp.o: ../boolean_operation.cpp
CMakeFiles/boolean_operation.dir/boolean_operation.cpp.o: CMakeFiles/boolean_operation.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/catherine/Research/CollisionDetection/AABBTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/boolean_operation.dir/boolean_operation.cpp.o"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/boolean_operation.dir/boolean_operation.cpp.o -MF CMakeFiles/boolean_operation.dir/boolean_operation.cpp.o.d -o CMakeFiles/boolean_operation.dir/boolean_operation.cpp.o -c /home/catherine/Research/CollisionDetection/AABBTest/boolean_operation.cpp

CMakeFiles/boolean_operation.dir/boolean_operation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/boolean_operation.dir/boolean_operation.cpp.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/catherine/Research/CollisionDetection/AABBTest/boolean_operation.cpp > CMakeFiles/boolean_operation.dir/boolean_operation.cpp.i

CMakeFiles/boolean_operation.dir/boolean_operation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/boolean_operation.dir/boolean_operation.cpp.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/catherine/Research/CollisionDetection/AABBTest/boolean_operation.cpp -o CMakeFiles/boolean_operation.dir/boolean_operation.cpp.s

# Object files for target boolean_operation
boolean_operation_OBJECTS = \
"CMakeFiles/boolean_operation.dir/boolean_operation.cpp.o"

# External object files for target boolean_operation
boolean_operation_EXTERNAL_OBJECTS =

bin/boolean_operation: CMakeFiles/boolean_operation.dir/boolean_operation.cpp.o
bin/boolean_operation: CMakeFiles/boolean_operation.dir/build.make
bin/boolean_operation: libgeometry.a
bin/boolean_operation: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
bin/boolean_operation: /usr/lib/x86_64-linux-gnu/libmpfr.so
bin/boolean_operation: /usr/lib/x86_64-linux-gnu/libgmp.so
bin/boolean_operation: CMakeFiles/boolean_operation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/catherine/Research/CollisionDetection/AABBTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/boolean_operation"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/boolean_operation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/boolean_operation.dir/build: bin/boolean_operation
.PHONY : CMakeFiles/boolean_operation.dir/build

CMakeFiles/boolean_operation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/boolean_operation.dir/cmake_clean.cmake
.PHONY : CMakeFiles/boolean_operation.dir/clean

CMakeFiles/boolean_operation.dir/depend:
	cd /home/catherine/Research/CollisionDetection/AABBTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/catherine/Research/CollisionDetection/AABBTest /home/catherine/Research/CollisionDetection/AABBTest /home/catherine/Research/CollisionDetection/AABBTest/build /home/catherine/Research/CollisionDetection/AABBTest/build /home/catherine/Research/CollisionDetection/AABBTest/build/CMakeFiles/boolean_operation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/boolean_operation.dir/depend
