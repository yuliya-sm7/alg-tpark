# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /snap/clion/61/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/61/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/yu/Рабочий стол/alg-tpark/DZ_5_1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/yu/Рабочий стол/alg-tpark/DZ_5_1/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/DZ_5_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DZ_5_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DZ_5_1.dir/flags.make

CMakeFiles/DZ_5_1.dir/main.cpp.o: CMakeFiles/DZ_5_1.dir/flags.make
CMakeFiles/DZ_5_1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/yu/Рабочий стол/alg-tpark/DZ_5_1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DZ_5_1.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DZ_5_1.dir/main.cpp.o -c "/home/yu/Рабочий стол/alg-tpark/DZ_5_1/main.cpp"

CMakeFiles/DZ_5_1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DZ_5_1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/yu/Рабочий стол/alg-tpark/DZ_5_1/main.cpp" > CMakeFiles/DZ_5_1.dir/main.cpp.i

CMakeFiles/DZ_5_1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DZ_5_1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/yu/Рабочий стол/alg-tpark/DZ_5_1/main.cpp" -o CMakeFiles/DZ_5_1.dir/main.cpp.s

# Object files for target DZ_5_1
DZ_5_1_OBJECTS = \
"CMakeFiles/DZ_5_1.dir/main.cpp.o"

# External object files for target DZ_5_1
DZ_5_1_EXTERNAL_OBJECTS =

DZ_5_1: CMakeFiles/DZ_5_1.dir/main.cpp.o
DZ_5_1: CMakeFiles/DZ_5_1.dir/build.make
DZ_5_1: CMakeFiles/DZ_5_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/yu/Рабочий стол/alg-tpark/DZ_5_1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DZ_5_1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DZ_5_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DZ_5_1.dir/build: DZ_5_1

.PHONY : CMakeFiles/DZ_5_1.dir/build

CMakeFiles/DZ_5_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DZ_5_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DZ_5_1.dir/clean

CMakeFiles/DZ_5_1.dir/depend:
	cd "/home/yu/Рабочий стол/alg-tpark/DZ_5_1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/yu/Рабочий стол/alg-tpark/DZ_5_1" "/home/yu/Рабочий стол/alg-tpark/DZ_5_1" "/home/yu/Рабочий стол/alg-tpark/DZ_5_1/cmake-build-debug" "/home/yu/Рабочий стол/alg-tpark/DZ_5_1/cmake-build-debug" "/home/yu/Рабочий стол/alg-tpark/DZ_5_1/cmake-build-debug/CMakeFiles/DZ_5_1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/DZ_5_1.dir/depend
