option(IVR_SOURCES "Select the source code of Interactive Volumetric Render for compilation" ON)

if(IVR_SOURCES) 
    message(STATUS "Configure the source code of Interactive Volumetric Render")
    set(
        SOURCES
        # "${CMAKE_CURRENT_LIST_DIR}/Interactive-Volumetric-Renderer/hellobgfx.cpp"
        "./Interactive-Volumetric-Renderer/cubes.cpp"
    )

    add_executable(${PROJECT_NAME} ${SOURCES})

    set(SHADERS_DIR "${CMAKE_SOURCE_DIR}/assets/shaders/")

    # compile the shaders
    bgfx_compile_shaders(
        TYPE VERTEX
        SHADERS "${SHADERS_DIR}/cubes/vs_cubes.sc"
        VARYING_DEF "${SHADERS_DIR}/cubes/varying.def.sc"
        OUTPUT_DIR "${SHADERS_DIR}/cubes"
    )

    bgfx_compile_shaders(
        TYPE FRAGMENT
        SHADERS "${SHADERS_DIR}/cubes/fs_cubes.sc"
        VARYING_DEF "${SHADERS_DIR}/cubes/varying.def.sc"
        OUTPUT_DIR "${SHADERS_DIR}/cubes"
    )

    # inluce necessary headfiles
    target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include"
    )

    # link necessary libs
    target_link_libraries( 
        ${PROJECT_NAME}
        PUBLIC
        IVR-LIB
    )
endif()
