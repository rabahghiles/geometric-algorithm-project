# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "E:\master2iot\Advanced Algorithms\exersises\geometric_algorithm_project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "E:\master2iot\Advanced Algorithms\exersises\geometric_algorithm_project\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\finalproject.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\finalproject.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\finalproject.dir\flags.make

CMakeFiles\finalproject.dir\main.cpp.obj: CMakeFiles\finalproject.dir\flags.make
CMakeFiles\finalproject.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="E:\master2iot\Advanced Algorithms\exersises\geometric_algorithm_project\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/finalproject.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\finalproject.dir\main.cpp.obj /FdCMakeFiles\finalproject.dir\ /FS -c "E:\master2iot\Advanced Algorithms\exersises\geometric_algorithm_project\main.cpp"
<<

CMakeFiles\finalproject.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/finalproject.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\finalproject.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "E:\master2iot\Advanced Algorithms\exersises\geometric_algorithm_project\main.cpp"
<<

CMakeFiles\finalproject.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/finalproject.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\finalproject.dir\main.cpp.s /c "E:\master2iot\Advanced Algorithms\exersises\geometric_algorithm_project\main.cpp"
<<

# Object files for target finalproject
finalproject_OBJECTS = \
"CMakeFiles\finalproject.dir\main.cpp.obj"

# External object files for target finalproject
finalproject_EXTERNAL_OBJECTS =

finalproject.exe: CMakeFiles\finalproject.dir\main.cpp.obj
finalproject.exe: CMakeFiles\finalproject.dir\build.make
finalproject.exe: CMakeFiles\finalproject.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="E:\master2iot\Advanced Algorithms\exersises\geometric_algorithm_project\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable finalproject.exe"
	"C:\Program Files\JetBrains\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\finalproject.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\finalproject.dir\objects1.rsp @<<
 /out:finalproject.exe /implib:finalproject.lib /pdb:"E:\master2iot\Advanced Algorithms\exersises\geometric_algorithm_project\cmake-build-debug\finalproject.pdb" /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\finalproject.dir\build: finalproject.exe

.PHONY : CMakeFiles\finalproject.dir\build

CMakeFiles\finalproject.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\finalproject.dir\cmake_clean.cmake
.PHONY : CMakeFiles\finalproject.dir\clean

CMakeFiles\finalproject.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "E:\master2iot\Advanced Algorithms\exersises\geometric_algorithm_project" "E:\master2iot\Advanced Algorithms\exersises\geometric_algorithm_project" "E:\master2iot\Advanced Algorithms\exersises\geometric_algorithm_project\cmake-build-debug" "E:\master2iot\Advanced Algorithms\exersises\geometric_algorithm_project\cmake-build-debug" "E:\master2iot\Advanced Algorithms\exersises\geometric_algorithm_project\cmake-build-debug\CMakeFiles\finalproject.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\finalproject.dir\depend
