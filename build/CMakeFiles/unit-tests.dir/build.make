# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tarediiran/MyPrograms/MazeGenerator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tarediiran/MyPrograms/MazeGenerator/build

# Include any dependencies generated for this target.
include CMakeFiles/unit-tests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/unit-tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/unit-tests.dir/flags.make

CMakeFiles/unit-tests.dir/unit_tests.cpp.o: CMakeFiles/unit-tests.dir/flags.make
CMakeFiles/unit-tests.dir/unit_tests.cpp.o: ../unit_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tarediiran/MyPrograms/MazeGenerator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/unit-tests.dir/unit_tests.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit-tests.dir/unit_tests.cpp.o -c /home/tarediiran/MyPrograms/MazeGenerator/unit_tests.cpp

CMakeFiles/unit-tests.dir/unit_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit-tests.dir/unit_tests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tarediiran/MyPrograms/MazeGenerator/unit_tests.cpp > CMakeFiles/unit-tests.dir/unit_tests.cpp.i

CMakeFiles/unit-tests.dir/unit_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit-tests.dir/unit_tests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tarediiran/MyPrograms/MazeGenerator/unit_tests.cpp -o CMakeFiles/unit-tests.dir/unit_tests.cpp.s

CMakeFiles/unit-tests.dir/unit_tests.cpp.o.requires:

.PHONY : CMakeFiles/unit-tests.dir/unit_tests.cpp.o.requires

CMakeFiles/unit-tests.dir/unit_tests.cpp.o.provides: CMakeFiles/unit-tests.dir/unit_tests.cpp.o.requires
	$(MAKE) -f CMakeFiles/unit-tests.dir/build.make CMakeFiles/unit-tests.dir/unit_tests.cpp.o.provides.build
.PHONY : CMakeFiles/unit-tests.dir/unit_tests.cpp.o.provides

CMakeFiles/unit-tests.dir/unit_tests.cpp.o.provides.build: CMakeFiles/unit-tests.dir/unit_tests.cpp.o


CMakeFiles/unit-tests.dir/lodepng.cpp.o: CMakeFiles/unit-tests.dir/flags.make
CMakeFiles/unit-tests.dir/lodepng.cpp.o: ../lodepng.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tarediiran/MyPrograms/MazeGenerator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/unit-tests.dir/lodepng.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/unit-tests.dir/lodepng.cpp.o -c /home/tarediiran/MyPrograms/MazeGenerator/lodepng.cpp

CMakeFiles/unit-tests.dir/lodepng.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unit-tests.dir/lodepng.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tarediiran/MyPrograms/MazeGenerator/lodepng.cpp > CMakeFiles/unit-tests.dir/lodepng.cpp.i

CMakeFiles/unit-tests.dir/lodepng.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unit-tests.dir/lodepng.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tarediiran/MyPrograms/MazeGenerator/lodepng.cpp -o CMakeFiles/unit-tests.dir/lodepng.cpp.s

CMakeFiles/unit-tests.dir/lodepng.cpp.o.requires:

.PHONY : CMakeFiles/unit-tests.dir/lodepng.cpp.o.requires

CMakeFiles/unit-tests.dir/lodepng.cpp.o.provides: CMakeFiles/unit-tests.dir/lodepng.cpp.o.requires
	$(MAKE) -f CMakeFiles/unit-tests.dir/build.make CMakeFiles/unit-tests.dir/lodepng.cpp.o.provides.build
.PHONY : CMakeFiles/unit-tests.dir/lodepng.cpp.o.provides

CMakeFiles/unit-tests.dir/lodepng.cpp.o.provides.build: CMakeFiles/unit-tests.dir/lodepng.cpp.o


# Object files for target unit-tests
unit__tests_OBJECTS = \
"CMakeFiles/unit-tests.dir/unit_tests.cpp.o" \
"CMakeFiles/unit-tests.dir/lodepng.cpp.o"

# External object files for target unit-tests
unit__tests_EXTERNAL_OBJECTS =

unit-tests: CMakeFiles/unit-tests.dir/unit_tests.cpp.o
unit-tests: CMakeFiles/unit-tests.dir/lodepng.cpp.o
unit-tests: CMakeFiles/unit-tests.dir/build.make
unit-tests: CMakeFiles/unit-tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tarediiran/MyPrograms/MazeGenerator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable unit-tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unit-tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/unit-tests.dir/build: unit-tests

.PHONY : CMakeFiles/unit-tests.dir/build

CMakeFiles/unit-tests.dir/requires: CMakeFiles/unit-tests.dir/unit_tests.cpp.o.requires
CMakeFiles/unit-tests.dir/requires: CMakeFiles/unit-tests.dir/lodepng.cpp.o.requires

.PHONY : CMakeFiles/unit-tests.dir/requires

CMakeFiles/unit-tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/unit-tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/unit-tests.dir/clean

CMakeFiles/unit-tests.dir/depend:
	cd /home/tarediiran/MyPrograms/MazeGenerator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tarediiran/MyPrograms/MazeGenerator /home/tarediiran/MyPrograms/MazeGenerator /home/tarediiran/MyPrograms/MazeGenerator/build /home/tarediiran/MyPrograms/MazeGenerator/build /home/tarediiran/MyPrograms/MazeGenerator/build/CMakeFiles/unit-tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/unit-tests.dir/depend

