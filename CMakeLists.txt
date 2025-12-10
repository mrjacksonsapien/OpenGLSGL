cmake_minimum_required(VERSION 3.10)
project(OpenGLSGL)

set(CMAKE_CXX_STANDARD 17)

# Include paths
include_directories(include)
include_directories(external/glfw/include)
include_directories(external/glm)

# GLFW subdir
add_subdirectory(external/glfw)

# Collect all .cpp files
file(GLOB_RECURSE SRC_FILES src/*.cpp src/glad/*.src)

# === Embed shaders at build time ===

set(SHADER_DIR "${CMAKE_SOURCE_DIR}/shaders")
set(GENERATED_SHADER_DIR "${CMAKE_BINARY_DIR}/generated_shaders")
file(MAKE_DIRECTORY ${GENERATED_SHADER_DIR})

set(SHADER_FILES
    ${SHADER_DIR}/vertex.glsl
    ${SHADER_DIR}/fragment.glsl
)

set(GENERATED_SHADER_HEADERS "")

foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(SHADER_NAME ${SHADER_FILE} NAME_WE)
    set(OUTPUT_HEADER "${GENERATED_SHADER_DIR}/${SHADER_NAME}_shader.h")

    add_custom_command(
        OUTPUT ${OUTPUT_HEADER}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${GENERATED_SHADER_DIR}
        COMMAND ${CMAKE_COMMAND} -E echo "Embedding ${SHADER_NAME}.glsl into header"
        COMMAND ${CMAKE_COMMAND} -E env PYTHONIOENCODING=utf-8
            python -c "import pathlib; p=pathlib.Path(r'${OUTPUT_HEADER}'); s=pathlib.Path(r'${SHADER_FILE}').read_text(encoding='utf-8'); p.write_text(f'constexpr const char ${SHADER_NAME}_shader[] = R\"shader(\\n{s})shader\";\\n', encoding='utf-8')"
        DEPENDS ${SHADER_FILE}
        VERBATIM
    )

    list(APPEND GENERATED_SHADER_HEADERS ${OUTPUT_HEADER})
endforeach()

add_custom_target(embed_shaders ALL DEPENDS ${GENERATED_SHADER_HEADERS})

# === Build executable ===

add_executable(OpenGLSGL main.cpp src/glad/glad.c ${SRC_FILES})

add_dependencies(OpenGLSGL embed_shaders)

target_include_directories(OpenGLSGL PRIVATE ${GENERATED_SHADER_DIR})

target_link_libraries(OpenGLSGL glfw OpenGL32)
