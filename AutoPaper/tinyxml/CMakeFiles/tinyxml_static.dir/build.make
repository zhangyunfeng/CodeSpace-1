# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ken/KenHttpd/AutoPaper/tinyxml

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ken/KenHttpd/AutoPaper/tinyxml

# Include any dependencies generated for this target.
include CMakeFiles/tinyxml_static.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tinyxml_static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tinyxml_static.dir/flags.make

CMakeFiles/tinyxml_static.dir/tinystr.o: CMakeFiles/tinyxml_static.dir/flags.make
CMakeFiles/tinyxml_static.dir/tinystr.o: tinystr.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ken/KenHttpd/AutoPaper/tinyxml/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tinyxml_static.dir/tinystr.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tinyxml_static.dir/tinystr.o -c /home/ken/KenHttpd/AutoPaper/tinyxml/tinystr.cpp

CMakeFiles/tinyxml_static.dir/tinystr.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinyxml_static.dir/tinystr.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ken/KenHttpd/AutoPaper/tinyxml/tinystr.cpp > CMakeFiles/tinyxml_static.dir/tinystr.i

CMakeFiles/tinyxml_static.dir/tinystr.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinyxml_static.dir/tinystr.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ken/KenHttpd/AutoPaper/tinyxml/tinystr.cpp -o CMakeFiles/tinyxml_static.dir/tinystr.s

CMakeFiles/tinyxml_static.dir/tinystr.o.requires:
.PHONY : CMakeFiles/tinyxml_static.dir/tinystr.o.requires

CMakeFiles/tinyxml_static.dir/tinystr.o.provides: CMakeFiles/tinyxml_static.dir/tinystr.o.requires
	$(MAKE) -f CMakeFiles/tinyxml_static.dir/build.make CMakeFiles/tinyxml_static.dir/tinystr.o.provides.build
.PHONY : CMakeFiles/tinyxml_static.dir/tinystr.o.provides

CMakeFiles/tinyxml_static.dir/tinystr.o.provides.build: CMakeFiles/tinyxml_static.dir/tinystr.o

CMakeFiles/tinyxml_static.dir/tinyxmlparser.o: CMakeFiles/tinyxml_static.dir/flags.make
CMakeFiles/tinyxml_static.dir/tinyxmlparser.o: tinyxmlparser.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ken/KenHttpd/AutoPaper/tinyxml/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tinyxml_static.dir/tinyxmlparser.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tinyxml_static.dir/tinyxmlparser.o -c /home/ken/KenHttpd/AutoPaper/tinyxml/tinyxmlparser.cpp

CMakeFiles/tinyxml_static.dir/tinyxmlparser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinyxml_static.dir/tinyxmlparser.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ken/KenHttpd/AutoPaper/tinyxml/tinyxmlparser.cpp > CMakeFiles/tinyxml_static.dir/tinyxmlparser.i

CMakeFiles/tinyxml_static.dir/tinyxmlparser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinyxml_static.dir/tinyxmlparser.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ken/KenHttpd/AutoPaper/tinyxml/tinyxmlparser.cpp -o CMakeFiles/tinyxml_static.dir/tinyxmlparser.s

CMakeFiles/tinyxml_static.dir/tinyxmlparser.o.requires:
.PHONY : CMakeFiles/tinyxml_static.dir/tinyxmlparser.o.requires

CMakeFiles/tinyxml_static.dir/tinyxmlparser.o.provides: CMakeFiles/tinyxml_static.dir/tinyxmlparser.o.requires
	$(MAKE) -f CMakeFiles/tinyxml_static.dir/build.make CMakeFiles/tinyxml_static.dir/tinyxmlparser.o.provides.build
.PHONY : CMakeFiles/tinyxml_static.dir/tinyxmlparser.o.provides

CMakeFiles/tinyxml_static.dir/tinyxmlparser.o.provides.build: CMakeFiles/tinyxml_static.dir/tinyxmlparser.o

CMakeFiles/tinyxml_static.dir/tinyxmlerror.o: CMakeFiles/tinyxml_static.dir/flags.make
CMakeFiles/tinyxml_static.dir/tinyxmlerror.o: tinyxmlerror.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ken/KenHttpd/AutoPaper/tinyxml/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tinyxml_static.dir/tinyxmlerror.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tinyxml_static.dir/tinyxmlerror.o -c /home/ken/KenHttpd/AutoPaper/tinyxml/tinyxmlerror.cpp

CMakeFiles/tinyxml_static.dir/tinyxmlerror.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinyxml_static.dir/tinyxmlerror.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ken/KenHttpd/AutoPaper/tinyxml/tinyxmlerror.cpp > CMakeFiles/tinyxml_static.dir/tinyxmlerror.i

CMakeFiles/tinyxml_static.dir/tinyxmlerror.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinyxml_static.dir/tinyxmlerror.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ken/KenHttpd/AutoPaper/tinyxml/tinyxmlerror.cpp -o CMakeFiles/tinyxml_static.dir/tinyxmlerror.s

CMakeFiles/tinyxml_static.dir/tinyxmlerror.o.requires:
.PHONY : CMakeFiles/tinyxml_static.dir/tinyxmlerror.o.requires

CMakeFiles/tinyxml_static.dir/tinyxmlerror.o.provides: CMakeFiles/tinyxml_static.dir/tinyxmlerror.o.requires
	$(MAKE) -f CMakeFiles/tinyxml_static.dir/build.make CMakeFiles/tinyxml_static.dir/tinyxmlerror.o.provides.build
.PHONY : CMakeFiles/tinyxml_static.dir/tinyxmlerror.o.provides

CMakeFiles/tinyxml_static.dir/tinyxmlerror.o.provides.build: CMakeFiles/tinyxml_static.dir/tinyxmlerror.o

CMakeFiles/tinyxml_static.dir/tinyxml.o: CMakeFiles/tinyxml_static.dir/flags.make
CMakeFiles/tinyxml_static.dir/tinyxml.o: tinyxml.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ken/KenHttpd/AutoPaper/tinyxml/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tinyxml_static.dir/tinyxml.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tinyxml_static.dir/tinyxml.o -c /home/ken/KenHttpd/AutoPaper/tinyxml/tinyxml.cpp

CMakeFiles/tinyxml_static.dir/tinyxml.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tinyxml_static.dir/tinyxml.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ken/KenHttpd/AutoPaper/tinyxml/tinyxml.cpp > CMakeFiles/tinyxml_static.dir/tinyxml.i

CMakeFiles/tinyxml_static.dir/tinyxml.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tinyxml_static.dir/tinyxml.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ken/KenHttpd/AutoPaper/tinyxml/tinyxml.cpp -o CMakeFiles/tinyxml_static.dir/tinyxml.s

CMakeFiles/tinyxml_static.dir/tinyxml.o.requires:
.PHONY : CMakeFiles/tinyxml_static.dir/tinyxml.o.requires

CMakeFiles/tinyxml_static.dir/tinyxml.o.provides: CMakeFiles/tinyxml_static.dir/tinyxml.o.requires
	$(MAKE) -f CMakeFiles/tinyxml_static.dir/build.make CMakeFiles/tinyxml_static.dir/tinyxml.o.provides.build
.PHONY : CMakeFiles/tinyxml_static.dir/tinyxml.o.provides

CMakeFiles/tinyxml_static.dir/tinyxml.o.provides.build: CMakeFiles/tinyxml_static.dir/tinyxml.o

# Object files for target tinyxml_static
tinyxml_static_OBJECTS = \
"CMakeFiles/tinyxml_static.dir/tinystr.o" \
"CMakeFiles/tinyxml_static.dir/tinyxmlparser.o" \
"CMakeFiles/tinyxml_static.dir/tinyxmlerror.o" \
"CMakeFiles/tinyxml_static.dir/tinyxml.o"

# External object files for target tinyxml_static
tinyxml_static_EXTERNAL_OBJECTS =

libtinyxml.a: CMakeFiles/tinyxml_static.dir/tinystr.o
libtinyxml.a: CMakeFiles/tinyxml_static.dir/tinyxmlparser.o
libtinyxml.a: CMakeFiles/tinyxml_static.dir/tinyxmlerror.o
libtinyxml.a: CMakeFiles/tinyxml_static.dir/tinyxml.o
libtinyxml.a: CMakeFiles/tinyxml_static.dir/build.make
libtinyxml.a: CMakeFiles/tinyxml_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libtinyxml.a"
	$(CMAKE_COMMAND) -P CMakeFiles/tinyxml_static.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tinyxml_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tinyxml_static.dir/build: libtinyxml.a
.PHONY : CMakeFiles/tinyxml_static.dir/build

CMakeFiles/tinyxml_static.dir/requires: CMakeFiles/tinyxml_static.dir/tinystr.o.requires
CMakeFiles/tinyxml_static.dir/requires: CMakeFiles/tinyxml_static.dir/tinyxmlparser.o.requires
CMakeFiles/tinyxml_static.dir/requires: CMakeFiles/tinyxml_static.dir/tinyxmlerror.o.requires
CMakeFiles/tinyxml_static.dir/requires: CMakeFiles/tinyxml_static.dir/tinyxml.o.requires
.PHONY : CMakeFiles/tinyxml_static.dir/requires

CMakeFiles/tinyxml_static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tinyxml_static.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tinyxml_static.dir/clean

CMakeFiles/tinyxml_static.dir/depend:
	cd /home/ken/KenHttpd/AutoPaper/tinyxml && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ken/KenHttpd/AutoPaper/tinyxml /home/ken/KenHttpd/AutoPaper/tinyxml /home/ken/KenHttpd/AutoPaper/tinyxml /home/ken/KenHttpd/AutoPaper/tinyxml /home/ken/KenHttpd/AutoPaper/tinyxml/CMakeFiles/tinyxml_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tinyxml_static.dir/depend
