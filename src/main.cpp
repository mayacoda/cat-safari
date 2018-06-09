#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "shaders/Shader.h"
#include "renderer/Renderer.h"
#include "util/fileUtil.h"

#define DEBUG true

float x         = 0, y = 0;
float camX      = 0, camY = 0, camZ = -30;
float pitch     = 0, yaw = 0, roll = 0;
bool  isPressed = false;

// Window dimensions
const GLuint WIDTH = 1024, HEIGHT = 720;

void keyboardCallback(GLFWwindow*, int, int, int, int);

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Urban Safari", nullptr, nullptr);

    glfwSetKeyCallback(window, keyboardCallback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // sync with vsync or monitor's refresh rate

    glewExperimental = GL_TRUE;
    glewInit();

    Shader shader("basic", "basic");

    // READING FROM FILE ======================================= WORKS!!
    TexturedModel *flare = loadObjModel("stall", "stallreal");
    Texture &texture = flare->getTexture();

    texture.setShineDamper(5);
    texture.setReflectivity(2);


    Entity entityFromFile = Entity(*flare);

    Renderer renderer(WIDTH, HEIGHT);

    renderer.init();

    Camera camera = Camera();
    Light light = Light(glm::vec3(0, 0, -20), glm::vec3(0.8, 0.5, 1));

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        renderer.prepare();

        // update
//        camera.rotate(glm::vec3(pitch, yaw, roll));
        camera.move(glm::vec3(camX, camY, camZ));
        entityFromFile.increaseRotation(0, 0.01, 0);

        // render
        renderer.render(entityFromFile, shader, camera, light);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        isPressed = true;
    } else if (action == GLFW_RELEASE) {
        isPressed = false;
    }

    if (isPressed) {
        switch (key) {
            case GLFW_KEY_UP:
                camY += 0.1;
                yaw   = 0.1f;
                break;
            case GLFW_KEY_DOWN:
                camY -= 0.1;
                yaw   = -0.1f;
                break;
            case GLFW_KEY_LEFT:
                camX -= 0.1;
                pitch = -0.1f;
                break;
            case GLFW_KEY_RIGHT:
                camX += 0.1;
                pitch = 0.1f;
                break;
            case GLFW_KEY_S:
                camZ += 0.1;
                roll  = 0.1f;
                break;
            case GLFW_KEY_W:
                camZ -= 0.01;
                roll  = -0.1f;
                break;
        }
    }
}
