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
float camX      = 0, camY = 0, camZ = 0;
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

    GLfloat vertices[] = {
            -0.5f, 0.5f, -0.5f, 0, 0, 0, 0, 0,
            -0.5f, -0.5f, -0.5f, 0, 1, 0, 0, 0,
            0.5f, -0.5f, -0.5f, 1, 1, 0, 0, 0,
            0.5f, 0.5f, -0.5f, 1, 0, 0, 0, 0,
            -0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 0,
            -0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 0,
            0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 0,
            0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 0,
            0.5f, 0.5f, -0.5f, 0, 0, 0, 0, 0,
            0.5f, -0.5f, -0.5f, 0, 1, 0, 0, 0,
            0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 0,
            0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 0,
            -0.5f, 0.5f, -0.5f, 0, 0, 0, 0, 0,
            -0.5f, -0.5f, -0.5f, 0, 1, 0, 0, 0,
            -0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 0,
            -0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 0,
            -0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 0,
            -0.5f, 0.5f, -0.5f, 0, 1, 0, 0, 0,
            0.5f, 0.5f, -0.5f, 1, 1, 0, 0, 0,
            0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 0,
            -0.5f, -0.5f, 0.5f, 0, 0, 0, 0, 0,
            -0.5f, -0.5f, -0.5f, 0, 1, 0, 0, 0,
            0.5f, -0.5f, -0.5f, 1, 1, 0, 0, 0,
            0.5f, -0.5f, 0.5f, 1, 0, 0, 0

    };

    unsigned int indices[] = {
            0, 1, 3,
            3, 1, 2,
            4, 5, 7,
            7, 5, 6,
            8, 9, 11,
            11, 9, 10,
            12, 13, 15,
            15, 13, 14,
            16, 17, 19,
            19, 17, 18,
            20, 21, 23,
            23, 21, 22
    };

    Shader shader("basic", "basic");

    // READING FROM FILE ======================================= WORKS!!
    TexturedModel *flare = loadObjModel("stall");
    Entity entityFromFile = Entity(*flare);

    // FROM MAIN FUNCTION ON STACK ============================== WORKS

    Texture texture("./res/textures/flare.png");
    texture.bind();

    VertexArray va;

    VertexBuffer vb(vertices, sizeof(vertices));

    BufferLayout layout;
    layout.pushFloat(3, "position");
    layout.pushFloat(2, "textureCoords");
    layout.pushFloat(3, "normals");
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

    TexturedModel model  = TexturedModel(va, ib, texture);
    Entity entity = Entity(model);

    // POINTERS ============================================= WORKS

    auto * texture2 = new Texture("./res/textures/flare.png");
    texture2->bind();

    auto* va2 = new VertexArray();
    auto * vb1 = new VertexBuffer(vertices, sizeof(vertices));

    BufferLayout layout1;
    layout1.pushFloat(3, "position");
    layout1.pushFloat(2, "textureCoords");
    layout1.pushFloat(3, "normal");
    va2->addBuffer(*vb1, layout1);

    auto * ib2 = new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int));

    auto * pointersModel =  new TexturedModel(*va2, *ib2, *texture2);
    Entity pointersFromMain = Entity(*pointersModel);


    Renderer renderer(WIDTH, HEIGHT);

    renderer.init();

    Camera camera = Camera();
    camera.move(glm::vec3(0, 0, -50));

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        renderer.prepare();

        // update

        // render
        renderer.render(entityFromFile, shader, camera);
//        renderer.render(entity, shader, camera);
//        renderer.render(pointersFromMain, shader, camera);

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
                camY += 0.01;
                yaw   = 0.1f;
                break;
            case GLFW_KEY_DOWN:
                camY -= 0.01;
                yaw   = -0.1f;
                break;
            case GLFW_KEY_LEFT:
                camX -= 0.01;
                pitch = -0.1f;
                break;
            case GLFW_KEY_RIGHT:
                camX += 0.01;
                pitch = 0.1f;
                break;
            case GLFW_KEY_S:
                camZ += 0.01;
                roll  = 0.1f;
                break;
            case GLFW_KEY_W:
                camZ -= 0.01;
                roll  = -0.1f;
                break;
        }
    }
}
