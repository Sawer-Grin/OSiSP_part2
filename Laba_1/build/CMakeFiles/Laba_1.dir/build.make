# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\CMake\bin\cmake.exe

# The command to remove a file.
RM = C:\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Study\OSiSP_part2\Laba_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Study\OSiSP_part2\Laba_1\build

# Include any dependencies generated for this target.
include CMakeFiles/Laba_1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Laba_1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Laba_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Laba_1.dir/flags.make

CMakeFiles/Laba_1.dir/main.cpp.obj: CMakeFiles/Laba_1.dir/flags.make
CMakeFiles/Laba_1.dir/main.cpp.obj: D:/Study/OSiSP_part2/Laba_1/main.cpp
CMakeFiles/Laba_1.dir/main.cpp.obj: CMakeFiles/Laba_1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Study\OSiSP_part2\Laba_1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Laba_1.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Laba_1.dir/main.cpp.obj -MF CMakeFiles\Laba_1.dir\main.cpp.obj.d -o CMakeFiles\Laba_1.dir\main.cpp.obj -c D:\Study\OSiSP_part2\Laba_1\main.cpp

CMakeFiles/Laba_1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Laba_1.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Study\OSiSP_part2\Laba_1\main.cpp > CMakeFiles\Laba_1.dir\main.cpp.i

CMakeFiles/Laba_1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Laba_1.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Study\OSiSP_part2\Laba_1\main.cpp -o CMakeFiles\Laba_1.dir\main.cpp.s

# Object files for target Laba_1
Laba_1_OBJECTS = \
"CMakeFiles/Laba_1.dir/main.cpp.obj"

# External object files for target Laba_1
Laba_1_EXTERNAL_OBJECTS =

Laba_1.exe: CMakeFiles/Laba_1.dir/main.cpp.obj
Laba_1.exe: CMakeFiles/Laba_1.dir/build.make
Laba_1.exe: CMakeFiles/Laba_1.dir/linklibs.rsp
Laba_1.exe: CMakeFiles/Laba_1.dir/objects1.rsp
Laba_1.exe: CMakeFiles/Laba_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Study\OSiSP_part2\Laba_1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Laba_1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Laba_1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Laba_1.dir/build: Laba_1.exe
.PHONY : CMakeFiles/Laba_1.dir/build

CMakeFiles/Laba_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Laba_1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Laba_1.dir/clean

CMakeFiles/Laba_1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Study\OSiSP_part2\Laba_1 D:\Study\OSiSP_part2\Laba_1 D:\Study\OSiSP_part2\Laba_1\build D:\Study\OSiSP_part2\Laba_1\build D:\Study\OSiSP_part2\Laba_1\build\CMakeFiles\Laba_1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Laba_1.dir/depend

