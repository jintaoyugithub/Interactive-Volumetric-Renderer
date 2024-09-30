set(
    SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

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

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/app/)
    

