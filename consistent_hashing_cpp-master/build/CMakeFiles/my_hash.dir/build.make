# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/build

# Include any dependencies generated for this target.
include CMakeFiles/my_hash.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/my_hash.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_hash.dir/flags.make

CMakeFiles/my_hash.dir/main.cpp.o: CMakeFiles/my_hash.dir/flags.make
CMakeFiles/my_hash.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_hash.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_hash.dir/main.cpp.o -c /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/main.cpp

CMakeFiles/my_hash.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_hash.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/main.cpp > CMakeFiles/my_hash.dir/main.cpp.i

CMakeFiles/my_hash.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_hash.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/main.cpp -o CMakeFiles/my_hash.dir/main.cpp.s

CMakeFiles/my_hash.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/my_hash.dir/main.cpp.o.requires

CMakeFiles/my_hash.dir/main.cpp.o.provides: CMakeFiles/my_hash.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/my_hash.dir/build.make CMakeFiles/my_hash.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/my_hash.dir/main.cpp.o.provides

CMakeFiles/my_hash.dir/main.cpp.o.provides.build: CMakeFiles/my_hash.dir/main.cpp.o


CMakeFiles/my_hash.dir/my_hash.cpp.o: CMakeFiles/my_hash.dir/flags.make
CMakeFiles/my_hash.dir/my_hash.cpp.o: ../my_hash.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_hash.dir/my_hash.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_hash.dir/my_hash.cpp.o -c /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/my_hash.cpp

CMakeFiles/my_hash.dir/my_hash.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_hash.dir/my_hash.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/my_hash.cpp > CMakeFiles/my_hash.dir/my_hash.cpp.i

CMakeFiles/my_hash.dir/my_hash.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_hash.dir/my_hash.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/my_hash.cpp -o CMakeFiles/my_hash.dir/my_hash.cpp.s

CMakeFiles/my_hash.dir/my_hash.cpp.o.requires:

.PHONY : CMakeFiles/my_hash.dir/my_hash.cpp.o.requires

CMakeFiles/my_hash.dir/my_hash.cpp.o.provides: CMakeFiles/my_hash.dir/my_hash.cpp.o.requires
	$(MAKE) -f CMakeFiles/my_hash.dir/build.make CMakeFiles/my_hash.dir/my_hash.cpp.o.provides.build
.PHONY : CMakeFiles/my_hash.dir/my_hash.cpp.o.provides

CMakeFiles/my_hash.dir/my_hash.cpp.o.provides.build: CMakeFiles/my_hash.dir/my_hash.cpp.o


# Object files for target my_hash
my_hash_OBJECTS = \
"CMakeFiles/my_hash.dir/main.cpp.o" \
"CMakeFiles/my_hash.dir/my_hash.cpp.o"

# External object files for target my_hash
my_hash_EXTERNAL_OBJECTS =

my_hash: CMakeFiles/my_hash.dir/main.cpp.o
my_hash: CMakeFiles/my_hash.dir/my_hash.cpp.o
my_hash: CMakeFiles/my_hash.dir/build.make
my_hash: CMakeFiles/my_hash.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable my_hash"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_hash.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_hash.dir/build: my_hash

.PHONY : CMakeFiles/my_hash.dir/build

CMakeFiles/my_hash.dir/requires: CMakeFiles/my_hash.dir/main.cpp.o.requires
CMakeFiles/my_hash.dir/requires: CMakeFiles/my_hash.dir/my_hash.cpp.o.requires

.PHONY : CMakeFiles/my_hash.dir/requires

CMakeFiles/my_hash.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_hash.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_hash.dir/clean

CMakeFiles/my_hash.dir/depend:
	cd /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/build /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/build /home/yhb/test/Consistent_Hashing/consistent_hashing_cpp-master/build/CMakeFiles/my_hash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_hash.dir/depend
