set(
    SOURCES
    "./utils/bgfx_utils.cpp"
    "./utils/entry/entry.cpp"
    "./utils/entry/cmd.cpp"
    "./utils/entry/input.cpp"
)

# file(
#    GLOB_RECURSE
#    SOURCES
#    "*.cpp"
# )

set(
    LIB_NAME
    "IVR-LIB"
)

# Necessary for xos api NSWindow and dispatch_sync
find_library(COCOA_LIBRARY Cocoa)
find_library(FOUNDATION_LIBRARY Foundation)

# specific for mac arm
set(CMAKE_OSX_ARCHITECTURES "arm64")


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
    ${COCOA_LIBRARY} 
    ${FOUNDATION_LIBRARY}
)
