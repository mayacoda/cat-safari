#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "shaders/Shader.h"
#include "renderer/Renderer.h"
#include "texture/Texture.h"

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

    Texture texture("./res/textures/flare.png");
    texture.bind();

    Shader shader("basic", "basic");
    shader.bind();

    shader.setUniform1i("u_texture", 0);

    GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    VertexArray va;

    VertexBuffer vb(vertices, 4 * 4 * sizeof(float));

    BufferLayout layout;
    layout.pushFloat(2);
    layout.pushFloat(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    float g   = 0;
    float inc = 0.01f;

    vb.unbind();
    shader.unbind();
    va.unbind();
    ib.unbind();

    Renderer renderer;

    renderer.init();

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activiated (key pressed,
        // mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        if (g > 1 || g < 0) inc = -inc;
        g += inc;

        renderer.prepare();

        shader.bind();
        shader.setUniform4f("u_color", 0.3f, 0, g, 1.0f);

        renderer.render(va, ib, shader);

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