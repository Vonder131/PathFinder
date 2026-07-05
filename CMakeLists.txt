# CMakeList.txt : CMake project for PathFinder include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("PathFinder")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c" "src/*.h")
add_subdirectory(external/raylib)
include_directories(
    src
    external/raylib/src      
)
# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${SOURCES} )


# Link to raylib and its dependencies
target_link_libraries(${PROJECT_NAME} raylib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET PathFinder PROPERTY CXX_STANDARD 20)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

# Only run this check on Linux (UNIX but not macOS)
if (UNIX AND NOT APPLE)
    # Try to find the X11 package
    find_package(X11 QUIET)
    
    # If X11 is not found, stop the build and tell the user how to fix it
    if (NOT X11_FOUND)
        message(FATAL_ERROR 
            "==================================================================\n"
            " Missing Graphics Dependencies! \n"
            " Your system is missing the X11 or Wayland development headers \n"
            " required to compile this project.\n"
            " \n"
            " If you are on Ubuntu or Pop!_OS, run the following command:\n"
            " sudo apt install libasound2-dev libx11-dev libxrandr-dev \\ \n"
            " libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev \\ \n"
            " libxinerama-dev libwayland-dev libxkbcommon-dev \n"
            "=================================================================="
        )
    endif()
endif()
# TODO: Add tests and install targets if needed.
