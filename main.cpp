#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vertex_shader.h"
#include "fragment_shader.h"

// Resize buffer when the window is resized
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Load shader source file as a string
std::string loadShaderSource(const char *path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Compile the shader into OpenGL bytecode
unsigned int compileShader(unsigned int type, const char *src) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(id, 512, nullptr, log);
        std::cerr << "Shader compilation error:\n" << log << std::endl;
    }

    return id;
}

// No more file loading
unsigned int createShaderProgramFromMemory(const char* vertexSrc, const char* fragmentSrc) {
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSrc);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, 512, nullptr, log);
        std::cerr << "Shader program linking error:\n" << log << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

// Create shader program from files at run time
unsigned int createShaderProgram(const std::string &vertexPath, const std::string &fragmentPath) {
    std::string vertexCode = loadShaderSource(vertexPath.c_str());
    std::string fragmentCode = loadShaderSource(fragmentPath.c_str());

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexCode.c_str());
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

    unsigned int program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    // Check for linking errors
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, 512, nullptr, log);
        std::cerr << "Shader program linking error:\n" << log << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main() {
    glfwInit(); // Start glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Tell glfw which major (latest) version of OpenGL I'm using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Tell glfw which minor (lowest) version of OpenGL I'm using
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Tell glfw I'm using OpenGL core profile

    GLFWwindow* window = glfwCreateWindow(800, 800, "MyFirstOpenGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Make window the current context for rendering
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set up the callback

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) { // Load OpenGL functions pointers (at runtime)
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float vertices[] = {
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f
    };

    unsigned int indices[] = { // Define triangles
        0, 1, 2,
        0, 2, 3
    };

    // Create vertex array and buffers
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO); // VAO for vertex attributes configurations (position, color, etc.)
    glGenBuffers(1, &VBO); // VBO stores raw vertex data on GPU
    glGenBuffers(1, &EBO); // EBO for elements (like triangles)

    // Bind buffers so subsequent calls affect them (state machine)
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // VAO remembers this EBO

    // VBO data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Static draw for now since data is not updated frequently

    // EBO data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // VAO data. Attributes reference the currently binded VBO at creation.

    // Parameters: index, size, type, normalized, stride, pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Define how to interpret position
    glEnableVertexAttribArray(0); // Pass index to enable it

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Color
    glEnableVertexAttribArray(1);

    // Create shader program. Vertex runs for each vertex and fragment runs for each pixel/fragment
    unsigned int shaderProgram = createShaderProgramFromMemory(vertex_shader, fragment_shader);

    glm::mat4 model = glm::mat4(1.0f); // Identity, no transformation
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f), // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // Look at origin
        glm::vec3(0.0f, 1.0f, 0.0f) // Up vector
    );

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f), // Field of view
        (float)(width / height), // Aspect ration
        0.1f, 100.0f // Near and far planes
    );

    glEnable(GL_DEPTH_TEST); // For proper 3D

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

        glUseProgram(shaderProgram); // Activate the shader program

        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO); // Automatically binds it's EBO and the attributes for rendering
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw EBO

        glfwSwapBuffers(window);
        glfwPollEvents();

        model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f)); // Testing rotation
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
