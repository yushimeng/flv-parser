# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ancece/github/flv-parser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ancece/github/flv-parser/build

# Include any dependencies generated for this target.
include CMakeFiles/flv-parser.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/flv-parser.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/flv-parser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/flv-parser.dir/flags.make

CMakeFiles/flv-parser.dir/main/main.cpp.o: CMakeFiles/flv-parser.dir/flags.make
CMakeFiles/flv-parser.dir/main/main.cpp.o: /Users/ancece/github/flv-parser/main/main.cpp
CMakeFiles/flv-parser.dir/main/main.cpp.o: CMakeFiles/flv-parser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ancece/github/flv-parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/flv-parser.dir/main/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flv-parser.dir/main/main.cpp.o -MF CMakeFiles/flv-parser.dir/main/main.cpp.o.d -o CMakeFiles/flv-parser.dir/main/main.cpp.o -c /Users/ancece/github/flv-parser/main/main.cpp

CMakeFiles/flv-parser.dir/main/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/flv-parser.dir/main/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ancece/github/flv-parser/main/main.cpp > CMakeFiles/flv-parser.dir/main/main.cpp.i

CMakeFiles/flv-parser.dir/main/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/flv-parser.dir/main/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ancece/github/flv-parser/main/main.cpp -o CMakeFiles/flv-parser.dir/main/main.cpp.s

CMakeFiles/flv-parser.dir/util/amf.cpp.o: CMakeFiles/flv-parser.dir/flags.make
CMakeFiles/flv-parser.dir/util/amf.cpp.o: /Users/ancece/github/flv-parser/util/amf.cpp
CMakeFiles/flv-parser.dir/util/amf.cpp.o: CMakeFiles/flv-parser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ancece/github/flv-parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/flv-parser.dir/util/amf.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flv-parser.dir/util/amf.cpp.o -MF CMakeFiles/flv-parser.dir/util/amf.cpp.o.d -o CMakeFiles/flv-parser.dir/util/amf.cpp.o -c /Users/ancece/github/flv-parser/util/amf.cpp

CMakeFiles/flv-parser.dir/util/amf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/flv-parser.dir/util/amf.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ancece/github/flv-parser/util/amf.cpp > CMakeFiles/flv-parser.dir/util/amf.cpp.i

CMakeFiles/flv-parser.dir/util/amf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/flv-parser.dir/util/amf.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ancece/github/flv-parser/util/amf.cpp -o CMakeFiles/flv-parser.dir/util/amf.cpp.s

CMakeFiles/flv-parser.dir/util/error.cpp.o: CMakeFiles/flv-parser.dir/flags.make
CMakeFiles/flv-parser.dir/util/error.cpp.o: /Users/ancece/github/flv-parser/util/error.cpp
CMakeFiles/flv-parser.dir/util/error.cpp.o: CMakeFiles/flv-parser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ancece/github/flv-parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/flv-parser.dir/util/error.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flv-parser.dir/util/error.cpp.o -MF CMakeFiles/flv-parser.dir/util/error.cpp.o.d -o CMakeFiles/flv-parser.dir/util/error.cpp.o -c /Users/ancece/github/flv-parser/util/error.cpp

CMakeFiles/flv-parser.dir/util/error.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/flv-parser.dir/util/error.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ancece/github/flv-parser/util/error.cpp > CMakeFiles/flv-parser.dir/util/error.cpp.i

CMakeFiles/flv-parser.dir/util/error.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/flv-parser.dir/util/error.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ancece/github/flv-parser/util/error.cpp -o CMakeFiles/flv-parser.dir/util/error.cpp.s

CMakeFiles/flv-parser.dir/util/streambuf.cpp.o: CMakeFiles/flv-parser.dir/flags.make
CMakeFiles/flv-parser.dir/util/streambuf.cpp.o: /Users/ancece/github/flv-parser/util/streambuf.cpp
CMakeFiles/flv-parser.dir/util/streambuf.cpp.o: CMakeFiles/flv-parser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ancece/github/flv-parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/flv-parser.dir/util/streambuf.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flv-parser.dir/util/streambuf.cpp.o -MF CMakeFiles/flv-parser.dir/util/streambuf.cpp.o.d -o CMakeFiles/flv-parser.dir/util/streambuf.cpp.o -c /Users/ancece/github/flv-parser/util/streambuf.cpp

CMakeFiles/flv-parser.dir/util/streambuf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/flv-parser.dir/util/streambuf.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ancece/github/flv-parser/util/streambuf.cpp > CMakeFiles/flv-parser.dir/util/streambuf.cpp.i

CMakeFiles/flv-parser.dir/util/streambuf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/flv-parser.dir/util/streambuf.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ancece/github/flv-parser/util/streambuf.cpp -o CMakeFiles/flv-parser.dir/util/streambuf.cpp.s

CMakeFiles/flv-parser.dir/flv/flvparser.cpp.o: CMakeFiles/flv-parser.dir/flags.make
CMakeFiles/flv-parser.dir/flv/flvparser.cpp.o: /Users/ancece/github/flv-parser/flv/flvparser.cpp
CMakeFiles/flv-parser.dir/flv/flvparser.cpp.o: CMakeFiles/flv-parser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ancece/github/flv-parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/flv-parser.dir/flv/flvparser.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/flv-parser.dir/flv/flvparser.cpp.o -MF CMakeFiles/flv-parser.dir/flv/flvparser.cpp.o.d -o CMakeFiles/flv-parser.dir/flv/flvparser.cpp.o -c /Users/ancece/github/flv-parser/flv/flvparser.cpp

CMakeFiles/flv-parser.dir/flv/flvparser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/flv-parser.dir/flv/flvparser.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ancece/github/flv-parser/flv/flvparser.cpp > CMakeFiles/flv-parser.dir/flv/flvparser.cpp.i

CMakeFiles/flv-parser.dir/flv/flvparser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/flv-parser.dir/flv/flvparser.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ancece/github/flv-parser/flv/flvparser.cpp -o CMakeFiles/flv-parser.dir/flv/flvparser.cpp.s

# Object files for target flv-parser
flv__parser_OBJECTS = \
"CMakeFiles/flv-parser.dir/main/main.cpp.o" \
"CMakeFiles/flv-parser.dir/util/amf.cpp.o" \
"CMakeFiles/flv-parser.dir/util/error.cpp.o" \
"CMakeFiles/flv-parser.dir/util/streambuf.cpp.o" \
"CMakeFiles/flv-parser.dir/flv/flvparser.cpp.o"

# External object files for target flv-parser
flv__parser_EXTERNAL_OBJECTS =

flv-parser: CMakeFiles/flv-parser.dir/main/main.cpp.o
flv-parser: CMakeFiles/flv-parser.dir/util/amf.cpp.o
flv-parser: CMakeFiles/flv-parser.dir/util/error.cpp.o
flv-parser: CMakeFiles/flv-parser.dir/util/streambuf.cpp.o
flv-parser: CMakeFiles/flv-parser.dir/flv/flvparser.cpp.o
flv-parser: CMakeFiles/flv-parser.dir/build.make
flv-parser: CMakeFiles/flv-parser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/ancece/github/flv-parser/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable flv-parser"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/flv-parser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/flv-parser.dir/build: flv-parser
.PHONY : CMakeFiles/flv-parser.dir/build

CMakeFiles/flv-parser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/flv-parser.dir/cmake_clean.cmake
.PHONY : CMakeFiles/flv-parser.dir/clean

CMakeFiles/flv-parser.dir/depend:
	cd /Users/ancece/github/flv-parser/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ancece/github/flv-parser /Users/ancece/github/flv-parser /Users/ancece/github/flv-parser/build /Users/ancece/github/flv-parser/build /Users/ancece/github/flv-parser/build/CMakeFiles/flv-parser.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/flv-parser.dir/depend
