option(IVR_SOURCES "Select the source code of Interactive Volumetric Render for compilation" ON)

if(IVR_SOURCES) 
    message(STATUS "Configure the source code of Interactive Volumetric Render")
    set(
        SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Interactive-Volumetric-Renderer/main.cpp"
    )

    add_executable(${PROJECT_NAME} ${SOURCES})

    # inluce necessary headfiles
    target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/exts/bgfx.cmake/bgfx/include"
        "${CMAKE_SOURCE_DIR}/exts/bgfx.cmake/bimg/include"
        "${CMAKE_SOURCE_DIR}/exts/bgfx.cmake/bx/include"
    )

    # link necessary libs
    target_link_libraries( 
        ${PROJECT_NAME}
        PUBLIC
        IVR-LIB
    )
endif()
