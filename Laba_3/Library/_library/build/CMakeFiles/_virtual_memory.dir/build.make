# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_SOURCE_DIR = /home/paulatreides/Study/Osisp/OSiSP_part2/Laba_3/Library/_library

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paulatreides/Study/Osisp/OSiSP_part2/Laba_3/Library/_library/build

# Include any dependencies generated for this target.
include CMakeFiles/_virtual_memory.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/_virtual_memory.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/_virtual_memory.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/_virtual_memory.dir/flags.make

CMakeFiles/_virtual_memory.dir/library.cpp.o: CMakeFiles/_virtual_memory.dir/flags.make
CMakeFiles/_virtual_memory.dir/library.cpp.o: /home/paulatreides/Study/Osisp/OSiSP_part2/Laba_3/Library/_library/library.cpp
CMakeFiles/_virtual_memory.dir/library.cpp.o: CMakeFiles/_virtual_memory.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paulatreides/Study/Osisp/OSiSP_part2/Laba_3/Library/_library/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/_virtual_memory.dir/library.cpp.o"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/_virtual_memory.dir/library.cpp.o -MF CMakeFiles/_virtual_memory.dir/library.cpp.o.d -o CMakeFiles/_virtual_memory.dir/library.cpp.o -c /home/paulatreides/Study/Osisp/OSiSP_part2/Laba_3/Library/_library/library.cpp

CMakeFiles/_virtual_memory.dir/library.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/_virtual_memory.dir/library.cpp.i"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paulatreides/Study/Osisp/OSiSP_part2/Laba_3/Library/_library/library.cpp > CMakeFiles/_virtual_memory.dir/library.cpp.i

CMakeFiles/_virtual_memory.dir/library.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/_virtual_memory.dir/library.cpp.s"
	/usr/bin/x86_64-w64-mingw32-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paulatreides/Study/Osisp/OSiSP_part2/Laba_3/Library/_library/library.cpp -o CMakeFiles/_virtual_memory.dir/library.cpp.s

_virtual_memory: CMakeFiles/_virtual_memory.dir/library.cpp.o
_virtual_memory: CMakeFiles/_virtual_memory.dir/build.make
.PHONY : _virtual_memory

# Rule to build all files generated by this target.
CMakeFiles/_virtual_memory.dir/build: _virtual_memory
.PHONY : CMakeFiles/_virtual_memory.dir/build

CMakeFiles/_virtual_memory.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/_virtual_memory.dir/cmake_clean.cmake
.PHONY : CMakeFiles/_virtual_memory.dir/clean

CMakeFiles/_virtual_memory.dir/depend:
	cd /home/paulatreides/Study/Osisp/OSiSP_part2/Laba_3/Library/_library/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paulatreides/Study/Osisp/OSiSP_part2/Laba_3/Library/_library /home/paulatreides/Study/Osisp/OSiSP_part2/Laba_3/Library/_library /home/paulatreides/Study/Osisp/OSiSP_part2/Laba_3/Library/_library/build /home/paulatreides/Study/Osisp/OSiSP_part2/Laba_3/Library/_library/build /home/paulatreides/Study/Osisp/OSiSP_part2/Laba_3/Library/_library/build/CMakeFiles/_virtual_memory.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/_virtual_memory.dir/depend

