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
include dep/glfw/tests/CMakeFiles/events.dir/depend.make

# Include the progress variables for this target.
include dep/glfw/tests/CMakeFiles/events.dir/progress.make

# Include the compile flags for this target's objects.
include dep/glfw/tests/CMakeFiles/events.dir/flags.make

dep/glfw/tests/CMakeFiles/events.dir/events.c.o: dep/glfw/tests/CMakeFiles/events.dir/flags.make
dep/glfw/tests/CMakeFiles/events.dir/events.c.o: ../dep/glfw/tests/events.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object dep/glfw/tests/CMakeFiles/events.dir/events.c.o"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/events.dir/events.c.o   -c "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/tests/events.c"

dep/glfw/tests/CMakeFiles/events.dir/events.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/events.dir/events.c.i"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/tests/events.c" > CMakeFiles/events.dir/events.c.i

dep/glfw/tests/CMakeFiles/events.dir/events.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/events.dir/events.c.s"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/tests/events.c" -o CMakeFiles/events.dir/events.c.s

dep/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o: dep/glfw/tests/CMakeFiles/events.dir/flags.make
dep/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o: ../dep/glfw/deps/getopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object dep/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/events.dir/__/deps/getopt.c.o   -c "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/deps/getopt.c"

dep/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/events.dir/__/deps/getopt.c.i"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/deps/getopt.c" > CMakeFiles/events.dir/__/deps/getopt.c.i

dep/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/events.dir/__/deps/getopt.c.s"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/deps/getopt.c" -o CMakeFiles/events.dir/__/deps/getopt.c.s

dep/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o: dep/glfw/tests/CMakeFiles/events.dir/flags.make
dep/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o: ../dep/glfw/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object dep/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/events.dir/__/deps/glad_gl.c.o   -c "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/deps/glad_gl.c"

dep/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/events.dir/__/deps/glad_gl.c.i"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/deps/glad_gl.c" > CMakeFiles/events.dir/__/deps/glad_gl.c.i

dep/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/events.dir/__/deps/glad_gl.c.s"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/deps/glad_gl.c" -o CMakeFiles/events.dir/__/deps/glad_gl.c.s

# Object files for target events
events_OBJECTS = \
"CMakeFiles/events.dir/events.c.o" \
"CMakeFiles/events.dir/__/deps/getopt.c.o" \
"CMakeFiles/events.dir/__/deps/glad_gl.c.o"

# External object files for target events
events_EXTERNAL_OBJECTS =

dep/glfw/tests/events: dep/glfw/tests/CMakeFiles/events.dir/events.c.o
dep/glfw/tests/events: dep/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o
dep/glfw/tests/events: dep/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o
dep/glfw/tests/events: dep/glfw/tests/CMakeFiles/events.dir/build.make
dep/glfw/tests/events: dep/glfw/src/libglfw3.a
dep/glfw/tests/events: /usr/lib/x86_64-linux-gnu/libm.so
dep/glfw/tests/events: /usr/lib/x86_64-linux-gnu/librt.so
dep/glfw/tests/events: /usr/lib/x86_64-linux-gnu/libm.so
dep/glfw/tests/events: /usr/lib/x86_64-linux-gnu/libX11.so
dep/glfw/tests/events: dep/glfw/tests/CMakeFiles/events.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable events"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/events.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dep/glfw/tests/CMakeFiles/events.dir/build: dep/glfw/tests/events

.PHONY : dep/glfw/tests/CMakeFiles/events.dir/build

dep/glfw/tests/CMakeFiles/events.dir/clean:
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && $(CMAKE_COMMAND) -P CMakeFiles/events.dir/cmake_clean.cmake
.PHONY : dep/glfw/tests/CMakeFiles/events.dir/clean

dep/glfw/tests/CMakeFiles/events.dir/depend:
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/tests" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests/CMakeFiles/events.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : dep/glfw/tests/CMakeFiles/events.dir/depend

