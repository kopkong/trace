# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/devtools/data/rel-16/external/apitrace

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/devtools/data/rel-16/external/apitrace/build

# Include any dependencies generated for this target.
include dispatch/CMakeFiles/glproc_egl.dir/depend.make

# Include the progress variables for this target.
include dispatch/CMakeFiles/glproc_egl.dir/progress.make

# Include the compile flags for this target's objects.
include dispatch/CMakeFiles/glproc_egl.dir/flags.make

dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o: dispatch/CMakeFiles/glproc_egl.dir/flags.make
dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o: ../dispatch/glproc_egl.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/devtools/data/rel-16/external/apitrace/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o"
	cd /home/devtools/data/rel-16/external/apitrace/build/dispatch && /home/devtools/data/android-ndk-r8e/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86_64/bin/arm-linux-androideabi-g++   $(CXX_DEFINES) $(CXX_FLAGS) -fPIC -o CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o -c /home/devtools/data/rel-16/external/apitrace/dispatch/glproc_egl.cpp

dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glproc_egl.dir/glproc_egl.cpp.i"
	cd /home/devtools/data/rel-16/external/apitrace/build/dispatch && /home/devtools/data/android-ndk-r8e/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86_64/bin/arm-linux-androideabi-g++  $(CXX_DEFINES) $(CXX_FLAGS) -fPIC -E /home/devtools/data/rel-16/external/apitrace/dispatch/glproc_egl.cpp > CMakeFiles/glproc_egl.dir/glproc_egl.cpp.i

dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glproc_egl.dir/glproc_egl.cpp.s"
	cd /home/devtools/data/rel-16/external/apitrace/build/dispatch && /home/devtools/data/android-ndk-r8e/toolchains/arm-linux-androideabi-4.7/prebuilt/linux-x86_64/bin/arm-linux-androideabi-g++  $(CXX_DEFINES) $(CXX_FLAGS) -fPIC -S /home/devtools/data/rel-16/external/apitrace/dispatch/glproc_egl.cpp -o CMakeFiles/glproc_egl.dir/glproc_egl.cpp.s

dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o.requires:
.PHONY : dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o.requires

dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o.provides: dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o.requires
	$(MAKE) -f dispatch/CMakeFiles/glproc_egl.dir/build.make dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o.provides.build
.PHONY : dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o.provides

dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o.provides.build: dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o

# Object files for target glproc_egl
glproc_egl_OBJECTS = \
"CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o"

# External object files for target glproc_egl
glproc_egl_EXTERNAL_OBJECTS =

../libs/armeabi-v7a/libglproc_egl.a: dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o
../libs/armeabi-v7a/libglproc_egl.a: dispatch/CMakeFiles/glproc_egl.dir/build.make
../libs/armeabi-v7a/libglproc_egl.a: dispatch/CMakeFiles/glproc_egl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library ../../libs/armeabi-v7a/libglproc_egl.a"
	cd /home/devtools/data/rel-16/external/apitrace/build/dispatch && $(CMAKE_COMMAND) -P CMakeFiles/glproc_egl.dir/cmake_clean_target.cmake
	cd /home/devtools/data/rel-16/external/apitrace/build/dispatch && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glproc_egl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dispatch/CMakeFiles/glproc_egl.dir/build: ../libs/armeabi-v7a/libglproc_egl.a
.PHONY : dispatch/CMakeFiles/glproc_egl.dir/build

dispatch/CMakeFiles/glproc_egl.dir/requires: dispatch/CMakeFiles/glproc_egl.dir/glproc_egl.cpp.o.requires
.PHONY : dispatch/CMakeFiles/glproc_egl.dir/requires

dispatch/CMakeFiles/glproc_egl.dir/clean:
	cd /home/devtools/data/rel-16/external/apitrace/build/dispatch && $(CMAKE_COMMAND) -P CMakeFiles/glproc_egl.dir/cmake_clean.cmake
.PHONY : dispatch/CMakeFiles/glproc_egl.dir/clean

dispatch/CMakeFiles/glproc_egl.dir/depend:
	cd /home/devtools/data/rel-16/external/apitrace/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/devtools/data/rel-16/external/apitrace /home/devtools/data/rel-16/external/apitrace/dispatch /home/devtools/data/rel-16/external/apitrace/build /home/devtools/data/rel-16/external/apitrace/build/dispatch /home/devtools/data/rel-16/external/apitrace/build/dispatch/CMakeFiles/glproc_egl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : dispatch/CMakeFiles/glproc_egl.dir/depend

