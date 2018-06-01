#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shaders/shaderLoader.h"
#include "util/GL.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"

#define DEBUG true

// Window dimensions
const GLuint WIDTH = 1024, HEIGHT = 720;

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Urban Safari", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // sync with vsync or monitor's refresh rate

    glewInit();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    GLuint shaderProgram = loadShader("basic", "basic");

    GLfloat vertices[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f,
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    VertexArray va;

    VertexBuffer vb(vertices, 4 * 2 * sizeof(float));

    BufferLayout layout;
    layout.pushFloat(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);


    float g = 0;
    float inc = 0.01f;

    int location = glGetUniformLocation(shaderProgram, "u_color");
    ASSERT(location != -1);
    glUniform4f(location, 0.3f, g, 0.3f, 1.0f);

    debug(glBindVertexArray(0));
    debug(glUseProgram(0));
    debug(glBindBuffer(GL_ARRAY_BUFFER, 0));
    debug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activiated (key pressed,
        // mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        if (g > 1 || g < 0) inc = -inc;
        g += inc;

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw our first triangle
        debug(glUseProgram(shaderProgram));
        debug(glUniform4f(location, 0.1f, g, 0.5f, 1.0f));

        va.bind();
        ib.bind();


        debug(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    va.unbind();
    vb.unbind();

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}