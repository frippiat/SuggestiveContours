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
include dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/depend.make

# Include the progress variables for this target.
include dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/progress.make

# Include the compile flags for this target's objects.
include dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/flags.make

dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/flags.make
dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o: ../dep/glfw/tests/triangle-vulkan.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o   -c "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/tests/triangle-vulkan.c"

dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/tests/triangle-vulkan.c" > CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.i

dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/tests/triangle-vulkan.c" -o CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.s

dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o: dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/flags.make
dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o: ../dep/glfw/deps/glad_vulkan.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o   -c "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/deps/glad_vulkan.c"

dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/deps/glad_vulkan.c" > CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.i

dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/deps/glad_vulkan.c" -o CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.s

# Object files for target triangle-vulkan
triangle__vulkan_OBJECTS = \
"CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o" \
"CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o"

# External object files for target triangle-vulkan
triangle__vulkan_EXTERNAL_OBJECTS =

dep/glfw/tests/triangle-vulkan: dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/triangle-vulkan.c.o
dep/glfw/tests/triangle-vulkan: dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/__/deps/glad_vulkan.c.o
dep/glfw/tests/triangle-vulkan: dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/build.make
dep/glfw/tests/triangle-vulkan: dep/glfw/src/libglfw3.a
dep/glfw/tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/libm.so
dep/glfw/tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/librt.so
dep/glfw/tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/libm.so
dep/glfw/tests/triangle-vulkan: /usr/lib/x86_64-linux-gnu/libX11.so
dep/glfw/tests/triangle-vulkan: dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable triangle-vulkan"
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/triangle-vulkan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/build: dep/glfw/tests/triangle-vulkan

.PHONY : dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/build

dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/clean:
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" && $(CMAKE_COMMAND) -P CMakeFiles/triangle-vulkan.dir/cmake_clean.cmake
.PHONY : dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/clean

dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/depend:
	cd "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/dep/glfw/tests" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests" "/home/vincent/Documents/Burgerlijk_Ingenieur_cw/Jaar_5/Telecom/Fundamentals of Computer Graphics/TP_Subdivision/GeomTP/build/dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : dep/glfw/tests/CMakeFiles/triangle-vulkan.dir/depend

