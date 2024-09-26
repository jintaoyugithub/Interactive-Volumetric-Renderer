cmake_minimum_required(VERSION 3.30.0)

# generate compile_commands.json for lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    Interactive-Volumetric-Renderer 
    VERSION 0.1.0 
    LANGUAGES C CXX
)

# Update submodules automatically
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE) 
        message(STATUS "Submodule update")
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT
        )       
        if (NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}.")
        endif()
    endif()
endif()


add_subdirectory(exts)
add_subdirectory(src)
add_subdirectory(apps)
