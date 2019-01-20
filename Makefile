# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /snap/clion/58/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/58/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sadegh/tank

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sadegh/tank

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/snap/clion/58/bin/cmake/linux/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/snap/clion/58/bin/cmake/linux/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sadegh/tank/CMakeFiles /home/sadegh/tank/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sadegh/tank/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named tank

# Build rule for target.
tank: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tank
.PHONY : tank

# fast build rule for target.
tank/fast:
	$(MAKE) -f CMakeFiles/tank.dir/build.make CMakeFiles/tank.dir/build
.PHONY : tank/fast

src/logic.o: src/logic.c.o

.PHONY : src/logic.o

# target to build an object file
src/logic.c.o:
	$(MAKE) -f CMakeFiles/tank.dir/build.make CMakeFiles/tank.dir/src/logic.c.o
.PHONY : src/logic.c.o

src/logic.i: src/logic.c.i

.PHONY : src/logic.i

# target to preprocess a source file
src/logic.c.i:
	$(MAKE) -f CMakeFiles/tank.dir/build.make CMakeFiles/tank.dir/src/logic.c.i
.PHONY : src/logic.c.i

src/logic.s: src/logic.c.s

.PHONY : src/logic.s

# target to generate assembly for a file
src/logic.c.s:
	$(MAKE) -f CMakeFiles/tank.dir/build.make CMakeFiles/tank.dir/src/logic.c.s
.PHONY : src/logic.c.s

src/physics.o: src/physics.c.o

.PHONY : src/physics.o

# target to build an object file
src/physics.c.o:
	$(MAKE) -f CMakeFiles/tank.dir/build.make CMakeFiles/tank.dir/src/physics.c.o
.PHONY : src/physics.c.o

src/physics.i: src/physics.c.i

.PHONY : src/physics.i

# target to preprocess a source file
src/physics.c.i:
	$(MAKE) -f CMakeFiles/tank.dir/build.make CMakeFiles/tank.dir/src/physics.c.i
.PHONY : src/physics.c.i

src/physics.s: src/physics.c.s

.PHONY : src/physics.s

# target to generate assembly for a file
src/physics.c.s:
	$(MAKE) -f CMakeFiles/tank.dir/build.make CMakeFiles/tank.dir/src/physics.c.s
.PHONY : src/physics.c.s

src/tank.o: src/tank.c.o

.PHONY : src/tank.o

# target to build an object file
src/tank.c.o:
	$(MAKE) -f CMakeFiles/tank.dir/build.make CMakeFiles/tank.dir/src/tank.c.o
.PHONY : src/tank.c.o

src/tank.i: src/tank.c.i

.PHONY : src/tank.i

# target to preprocess a source file
src/tank.c.i:
	$(MAKE) -f CMakeFiles/tank.dir/build.make CMakeFiles/tank.dir/src/tank.c.i
.PHONY : src/tank.c.i

src/tank.s: src/tank.c.s

.PHONY : src/tank.s

# target to generate assembly for a file
src/tank.c.s:
	$(MAKE) -f CMakeFiles/tank.dir/build.make CMakeFiles/tank.dir/src/tank.c.s
.PHONY : src/tank.c.s

src/view.o: src/view.c.o

.PHONY : src/view.o

# target to build an object file
src/view.c.o:
	$(MAKE) -f CMakeFiles/tank.dir/build.make CMakeFiles/tank.dir/src/view.c.o
.PHONY : src/view.c.o

src/view.i: src/view.c.i

.PHONY : src/view.i

# target to preprocess a source file
src/view.c.i:
	$(MAKE) -f CMakeFiles/tank.dir/build.make CMakeFiles/tank.dir/src/view.c.i
.PHONY : src/view.c.i

src/view.s: src/view.c.s

.PHONY : src/view.s

# target to generate assembly for a file
src/view.c.s:
	$(MAKE) -f CMakeFiles/tank.dir/build.make CMakeFiles/tank.dir/src/view.c.s
.PHONY : src/view.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... tank"
	@echo "... edit_cache"
	@echo "... src/logic.o"
	@echo "... src/logic.i"
	@echo "... src/logic.s"
	@echo "... src/physics.o"
	@echo "... src/physics.i"
	@echo "... src/physics.s"
	@echo "... src/tank.o"
	@echo "... src/tank.i"
	@echo "... src/tank.s"
	@echo "... src/view.o"
	@echo "... src/view.i"
	@echo "... src/view.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

