# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build"

# Include any dependencies generated for this target.
include dep/glad/CMakeFiles/glad.dir/depend.make

# Include the progress variables for this target.
include dep/glad/CMakeFiles/glad.dir/progress.make

# Include the compile flags for this target's objects.
include dep/glad/CMakeFiles/glad.dir/flags.make

dep/glad/CMakeFiles/glad.dir/src/glad.c.o: dep/glad/CMakeFiles/glad.dir/flags.make
dep/glad/CMakeFiles/glad.dir/src/glad.c.o: ../dep/glad/src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object dep/glad/CMakeFiles/glad.dir/src/glad.c.o"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glad" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glad.dir/src/glad.c.o   -c "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glad/src/glad.c"

dep/glad/CMakeFiles/glad.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glad.dir/src/glad.c.i"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glad" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glad/src/glad.c" > CMakeFiles/glad.dir/src/glad.c.i

dep/glad/CMakeFiles/glad.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glad.dir/src/glad.c.s"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glad" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glad/src/glad.c" -o CMakeFiles/glad.dir/src/glad.c.s

# Object files for target glad
glad_OBJECTS = \
"CMakeFiles/glad.dir/src/glad.c.o"

# External object files for target glad
glad_EXTERNAL_OBJECTS =

dep/glad/libglad.a: dep/glad/CMakeFiles/glad.dir/src/glad.c.o
dep/glad/libglad.a: dep/glad/CMakeFiles/glad.dir/build.make
dep/glad/libglad.a: dep/glad/CMakeFiles/glad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libglad.a"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glad" && $(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean_target.cmake
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glad" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dep/glad/CMakeFiles/glad.dir/build: dep/glad/libglad.a

.PHONY : dep/glad/CMakeFiles/glad.dir/build

dep/glad/CMakeFiles/glad.dir/clean:
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glad" && $(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean.cmake
.PHONY : dep/glad/CMakeFiles/glad.dir/clean

dep/glad/CMakeFiles/glad.dir/depend:
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glad" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glad" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glad/CMakeFiles/glad.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : dep/glad/CMakeFiles/glad.dir/depend

