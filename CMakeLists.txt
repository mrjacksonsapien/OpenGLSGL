cmake_minimum_required(VERSION 3.10)
project(OpenGLSGL)

set(CMAKE_CXX_STANDARD 17)

# Add GLFW and GLAD include paths
include_directories(include) # Use "" in code
include_directories(external/glfw/include) # Use <> in code
include_directories(external/glm) # Use <> in code

# Add GLFW as subdirectory
add_subdirectory(external/glfw)

# Collect all .cpp files in src/
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# Add your executable
add_executable(OpenGLSGL main.cpp src/glad.c ${SRC_FILES})

# Link to glfw (target from their CMakeLists)
target_link_libraries(OpenGLSGL glfw OpenGL32)