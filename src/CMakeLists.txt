set(
    SOURCES
    test.cpp
)

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
    "${CMAKE_SOURCE_DIR}/exts/bgfx.cmake/bgfx/examples/common"
    "${CMAKE_SOURCE_DIR}/exts/bgfx.cmake/bgfx/3rdparty"
)

# add necessary source files
file(GLOB COMMON_SRC "${CMAKE_SOURCE_DIR}/exts/bgfx.cmake/bgfx/examples/common/*.cpp")
file(GLOB MESHOPTIMIZER_SRC "${CMAKE_SOURCE_DIR}/exts/bgfx.cmake/bgfx/3rdparty/meshoptimizer/src/*.cpp")

target_sources(
    ${LIB_NAME}
    PUBLIC
    ${COMMON_SRC}
    ${MESHOPTIMIZER_SRC}
)

# link necessary libs
target_link_libraries( 
    ${LIB_NAME}
    PUBLIC
    bgfx
    bimg
    bx
    imgui
    glfw
    glm
)
