# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /private/var/folders/39/wgg_66gd7zg5_lr4gz0kr4080000gn/T/AppTranslocation/76FD4484-5448-4FE7-82A3-77C1D6FFDE13/d/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /private/var/folders/39/wgg_66gd7zg5_lr4gz0kr4080000gn/T/AppTranslocation/76FD4484-5448-4FE7-82A3-77C1D6FFDE13/d/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/aidenridgeway/CLionProjects/ProcedualProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/aidenridgeway/CLionProjects/ProcedualProject/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ProcedualProject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ProcedualProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProcedualProject.dir/flags.make

CMakeFiles/ProcedualProject.dir/main.cpp.o: CMakeFiles/ProcedualProject.dir/flags.make
CMakeFiles/ProcedualProject.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aidenridgeway/CLionProjects/ProcedualProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ProcedualProject.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ProcedualProject.dir/main.cpp.o -c /Users/aidenridgeway/CLionProjects/ProcedualProject/main.cpp

CMakeFiles/ProcedualProject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProcedualProject.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aidenridgeway/CLionProjects/ProcedualProject/main.cpp > CMakeFiles/ProcedualProject.dir/main.cpp.i

CMakeFiles/ProcedualProject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProcedualProject.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aidenridgeway/CLionProjects/ProcedualProject/main.cpp -o CMakeFiles/ProcedualProject.dir/main.cpp.s

# Object files for target ProcedualProject
ProcedualProject_OBJECTS = \
"CMakeFiles/ProcedualProject.dir/main.cpp.o"

# External object files for target ProcedualProject
ProcedualProject_EXTERNAL_OBJECTS =

ProcedualProject: CMakeFiles/ProcedualProject.dir/main.cpp.o
ProcedualProject: CMakeFiles/ProcedualProject.dir/build.make
ProcedualProject: CMakeFiles/ProcedualProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/aidenridgeway/CLionProjects/ProcedualProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ProcedualProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProcedualProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProcedualProject.dir/build: ProcedualProject

.PHONY : CMakeFiles/ProcedualProject.dir/build

CMakeFiles/ProcedualProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProcedualProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProcedualProject.dir/clean

CMakeFiles/ProcedualProject.dir/depend:
	cd /Users/aidenridgeway/CLionProjects/ProcedualProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/aidenridgeway/CLionProjects/ProcedualProject /Users/aidenridgeway/CLionProjects/ProcedualProject /Users/aidenridgeway/CLionProjects/ProcedualProject/cmake-build-debug /Users/aidenridgeway/CLionProjects/ProcedualProject/cmake-build-debug /Users/aidenridgeway/CLionProjects/ProcedualProject/cmake-build-debug/CMakeFiles/ProcedualProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProcedualProject.dir/depend
