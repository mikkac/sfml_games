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
CMAKE_SOURCE_DIR = /home/miki/repos/bob_was_alone

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/miki/repos/bob_was_alone/build

# Utility rule file for bob_was_alone-tidy.

# Include the progress variables for this target.
include CMakeFiles/bob_was_alone-tidy.dir/progress.make

CMakeFiles/bob_was_alone-tidy:
	/usr/bin/clang-tidy -p build /home/miki/repos/bob_was_alone/src/random.cpp -header-filter=.*

bob_was_alone-tidy: CMakeFiles/bob_was_alone-tidy
bob_was_alone-tidy: CMakeFiles/bob_was_alone-tidy.dir/build.make

.PHONY : bob_was_alone-tidy

# Rule to build all files generated by this target.
CMakeFiles/bob_was_alone-tidy.dir/build: bob_was_alone-tidy

.PHONY : CMakeFiles/bob_was_alone-tidy.dir/build

CMakeFiles/bob_was_alone-tidy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bob_was_alone-tidy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bob_was_alone-tidy.dir/clean

CMakeFiles/bob_was_alone-tidy.dir/depend:
	cd /home/miki/repos/bob_was_alone/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/miki/repos/bob_was_alone /home/miki/repos/bob_was_alone /home/miki/repos/bob_was_alone/build /home/miki/repos/bob_was_alone/build /home/miki/repos/bob_was_alone/build/CMakeFiles/bob_was_alone-tidy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bob_was_alone-tidy.dir/depend

