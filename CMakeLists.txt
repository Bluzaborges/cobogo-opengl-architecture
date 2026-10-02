cmake_minimum_required(VERSION 3.21)

project(cobogo-opengl-architecture VERSION 1.0.0 LANGUAGES CXX)

find_package(OpenGL REQUIRED)
set(GLEW_USE_STATIC_LIBS TRUE)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

set(COBOGO_OPENGL_ARCHITECTURE_SOURCES
    main.cpp
    include/Application.h
    include/Block.h
    include/Camera.h
    include/Chair.h
    include/Countertop.h
    include/Cube.h
    include/Cylinder.h
    include/Desk.h
    include/Fridge.h
    include/Grid.h
    include/Object.h
    include/Pendant.h
    include/SceneBuilder.h
    include/Shader.h
    include/Shelves.h
    include/Sofa.h
    include/Stand.h
    include/stb_image.h
    include/Table.h
    include/Television.h
    include/Texture.h
    src/Application.cpp
    src/Block.cpp
    src/Camera.cpp
    src/Chair.cpp
    src/Countertop.cpp
    src/Cube.cpp
    src/Cylinder.cpp
    src/Desk.cpp
    src/Fridge.cpp
    src/Grid.cpp
    src/Object.cpp
    src/Pendant.cpp
    src/SceneBuilder.cpp
    src/Shader.cpp
    src/Shelves.cpp
    src/Sofa.cpp
    src/Stand.cpp
    src/stb_image.cpp
    src/Table.cpp
    src/Television.cpp
    src/Texture.cpp
)

add_executable(cobogo-opengl-architecture ${COBOGO_OPENGL_ARCHITECTURE_SOURCES})

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES ${COBOGO_OPENGL_ARCHITECTURE_SOURCES}
)

target_compile_features(cobogo-opengl-architecture PRIVATE cxx_std_17)
target_include_directories(cobogo-opengl-architecture PRIVATE include)
target_link_libraries(
    cobogo-opengl-architecture
    PRIVATE
        OpenGL::GL
        GLEW::GLEW
        glfw
        glm::glm
)

if(MSVC)
    target_compile_options(cobogo-opengl-architecture PRIVATE /W4)
    set_source_files_properties(src/stb_image.cpp PROPERTIES COMPILE_OPTIONS /w)
else()
    target_compile_options(cobogo-opengl-architecture PRIVATE -Wall -Wextra -Wpedantic)
    set_source_files_properties(src/stb_image.cpp PROPERTIES COMPILE_OPTIONS -w)
endif()

foreach(resource_directory IN ITEMS shaders textures)
    add_custom_command(
        TARGET cobogo-opengl-architecture
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/${resource_directory}"
            "$<TARGET_FILE_DIR:cobogo-opengl-architecture>/${resource_directory}"
        VERBATIM
    )
endforeach()

if(WIN32)
    add_custom_command(
        TARGET cobogo-opengl-architecture
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:glfw>
            $<TARGET_FILE_DIR:cobogo-opengl-architecture>
        VERBATIM
    )
endif()
