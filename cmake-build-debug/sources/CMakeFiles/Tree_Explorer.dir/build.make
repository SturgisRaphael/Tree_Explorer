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
CMAKE_COMMAND = /home/raphael/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.4445.84/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/raphael/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.4445.84/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/raphael/Master-informatique/M1/Stage/Tree_Explorer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/cmake-build-debug

# Include any dependencies generated for this target.
include sources/CMakeFiles/Tree_Explorer.dir/depend.make

# Include the progress variables for this target.
include sources/CMakeFiles/Tree_Explorer.dir/progress.make

# Include the compile flags for this target's objects.
include sources/CMakeFiles/Tree_Explorer.dir/flags.make

sources/CMakeFiles/Tree_Explorer.dir/main.cpp.o: sources/CMakeFiles/Tree_Explorer.dir/flags.make
sources/CMakeFiles/Tree_Explorer.dir/main.cpp.o: ../sources/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/raphael/Master-informatique/M1/Stage/Tree_Explorer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sources/CMakeFiles/Tree_Explorer.dir/main.cpp.o"
	cd /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/cmake-build-debug/sources && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tree_Explorer.dir/main.cpp.o -c /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/sources/main.cpp

sources/CMakeFiles/Tree_Explorer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tree_Explorer.dir/main.cpp.i"
	cd /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/cmake-build-debug/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/sources/main.cpp > CMakeFiles/Tree_Explorer.dir/main.cpp.i

sources/CMakeFiles/Tree_Explorer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tree_Explorer.dir/main.cpp.s"
	cd /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/cmake-build-debug/sources && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/sources/main.cpp -o CMakeFiles/Tree_Explorer.dir/main.cpp.s

sources/CMakeFiles/Tree_Explorer.dir/main.cpp.o.requires:

.PHONY : sources/CMakeFiles/Tree_Explorer.dir/main.cpp.o.requires

sources/CMakeFiles/Tree_Explorer.dir/main.cpp.o.provides: sources/CMakeFiles/Tree_Explorer.dir/main.cpp.o.requires
	$(MAKE) -f sources/CMakeFiles/Tree_Explorer.dir/build.make sources/CMakeFiles/Tree_Explorer.dir/main.cpp.o.provides.build
.PHONY : sources/CMakeFiles/Tree_Explorer.dir/main.cpp.o.provides

sources/CMakeFiles/Tree_Explorer.dir/main.cpp.o.provides.build: sources/CMakeFiles/Tree_Explorer.dir/main.cpp.o


# Object files for target Tree_Explorer
Tree_Explorer_OBJECTS = \
"CMakeFiles/Tree_Explorer.dir/main.cpp.o"

# External object files for target Tree_Explorer
Tree_Explorer_EXTERNAL_OBJECTS =

sources/Tree_Explorer: sources/CMakeFiles/Tree_Explorer.dir/main.cpp.o
sources/Tree_Explorer: sources/CMakeFiles/Tree_Explorer.dir/build.make
sources/Tree_Explorer: sources/libcore.a
sources/Tree_Explorer: sources/CMakeFiles/Tree_Explorer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/raphael/Master-informatique/M1/Stage/Tree_Explorer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Tree_Explorer"
	cd /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/cmake-build-debug/sources && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tree_Explorer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sources/CMakeFiles/Tree_Explorer.dir/build: sources/Tree_Explorer

.PHONY : sources/CMakeFiles/Tree_Explorer.dir/build

sources/CMakeFiles/Tree_Explorer.dir/requires: sources/CMakeFiles/Tree_Explorer.dir/main.cpp.o.requires

.PHONY : sources/CMakeFiles/Tree_Explorer.dir/requires

sources/CMakeFiles/Tree_Explorer.dir/clean:
	cd /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/cmake-build-debug/sources && $(CMAKE_COMMAND) -P CMakeFiles/Tree_Explorer.dir/cmake_clean.cmake
.PHONY : sources/CMakeFiles/Tree_Explorer.dir/clean

sources/CMakeFiles/Tree_Explorer.dir/depend:
	cd /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/raphael/Master-informatique/M1/Stage/Tree_Explorer /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/sources /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/cmake-build-debug /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/cmake-build-debug/sources /home/raphael/Master-informatique/M1/Stage/Tree_Explorer/cmake-build-debug/sources/CMakeFiles/Tree_Explorer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sources/CMakeFiles/Tree_Explorer.dir/depend

