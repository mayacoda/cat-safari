#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "models/VertexArray.h"
#include "shaders/Shader.h"
#include "renderer/EntityRenderer.h"
#include "util/fileUtil.h"
#include "renderer/MasterRenderer.h"
#include "world/GameWorld.h"

#ifdef _WIN32
#define TIME_CORRECTION 1.0
#elif __APPLE__
#define TIME_CORRECTION 0.1 // make slower
#endif

#define DEBUG true

// Window dimensions
const GLuint WIDTH = 1024, HEIGHT = 720;

double t  = 0.0;
double dt = 0.0166666666666667;

GameWorld* world = new GameWorld();

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Urban Safari", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // sync with vsync or monitor's refresh rate

    glewExperimental = GL_TRUE;
    glewInit();

    world->init(window);

    glfwSetScrollCallback(window, scrollCallback);

    clock_t currentTime = clock();

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        clock_t newTime   = clock();
        double  frameTime = ((double) newTime - currentTime) / (CLOCKS_PER_SEC * TIME_CORRECTION);
        currentTime = newTime;

        // update
        while (frameTime > 0.0) {
            double deltaTime = glm::min(frameTime, dt);
            frameTime -= deltaTime;
            world->update(deltaTime);
            t += deltaTime;
        }
        // render
        world->render();

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    delete world;

    glfwTerminate();
    return 0;
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    world->scrollCallback(window, xOffset, yOffset);
}

