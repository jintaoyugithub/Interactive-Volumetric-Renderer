set(
    SOURCES
    test.cpp
    "./utils/bgfx_utils.cpp"
)

#file(
#    GLOB_RECURSE
#    SOURCES
#    "*.cpp"
#)

# remove entry_windows.cpp cause it has a main function
# list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/utils/entry/entry_windows.cpp")

set(
    LIB_NAME
    "IVR-LIB"
)

# Don't forget the static
add_library(
    ${LIB_NAME} 
    STATIC 
    ${SOURCES}
)

# include necessary headfiles
target_include_directories(
    ${LIB_NAME}
    PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/src/utils"
    "${CMAKE_SOURCE_DIR}/exts/bgfx.cmake/bgfx/3rdparty"
)

target_sources(
    ${LIB_NAME}
    PUBLIC
    ${COMMON_SRC}
)

# link necessary libs
target_link_libraries( 
    ${LIB_NAME}
    PUBLIC
    bx
    bimg
    bgfx
    imgui
    glfw
    glm
)
