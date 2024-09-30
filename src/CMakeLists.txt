set(
    SOURCES
    "./utils/test.cpp"
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
    "${CMAKE_SOURCE_DIR}/exts/llgl/include"
)

# link necessary libs
target_link_libraries( 
    ${LIB_NAME}
    PUBLIC
    glfw
    glm
    LLGL
)
