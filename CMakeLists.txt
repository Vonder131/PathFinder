# CMakeList.txt : CMake project for RaylibTemplate include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("RaylibTemplate")

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
  set_property(TARGET RaylibTemplate PROPERTY CXX_STANDARD 20)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)


# TODO: Add tests and install targets if needed.
