
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iomanip>
#include "../util/fileUtil.h"
#include "GameWorld.h"
#include "EntityLoader.h"
#include "../util/mouse-picking.h"

GameWorld::~GameWorld() {
    m_master->cleanUp();

    for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
        delete *it; // doesn't delete the model because the model doesn't belong to it
    }

    for (auto it = m_models.begin(); it != m_models.end(); it++) {
        delete *it;
    }

    for (auto it = m_terrains.begin(); it != m_terrains.end(); it++) {
        delete *it;
    }

    delete m_master;
    delete m_camera;
    delete m_light;
    delete m_gui;
}

void GameWorld::init(GLFWwindow* window) {
    m_window = window;
    m_light  = new Light(glm::vec3(0, 100, -20), glm::vec3(1, 1, 1));

    m_gui = new GUI();

    int width, height;
    glfwGetWindowSize(m_window, &width, &height);

    m_master = new MasterRenderer(width, height);

    EntityLoader::loadTerrain("./res/terrain.txt", m_entities, m_models);
    EntityLoader::loadCats(m_entities, m_models);

    TexturedModel* player = loadObjModel("player");

    m_player = new Player(player, glm::vec3(75, 0, -40), glm::vec3(0), 1);
    m_entities.push_back(m_player);
    m_models.push_back(player);

    m_camera = new Camera(m_player);

    m_terrains.push_back(new Terrain(0, 0));
}

void GameWorld::update(double deltaTime) {
    pollKeyboard();
    pollMouse();

    m_player->update(static_cast<float>(deltaTime));
    m_camera->update();
}

void GameWorld::render() const {

    for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
        m_master->processEntity(*it);
    }

    for (auto it = m_terrains.begin(); it != m_terrains.end(); it++) {
        m_master->processTerrain(*it);
    }

    m_master->render(*m_light, *m_camera, *m_gui);
}

void GameWorld::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {

    m_camera->calculateZoom(yOffset);
}

void GameWorld::pollKeyboard() const {

    if (glfwGetKey(m_window, GLFW_KEY_W)) {
        m_player->setSpeed(Player::MAX_SPEED);
    } else if (glfwGetKey(m_window, GLFW_KEY_S)) {
        m_player->setSpeed(-Player::MAX_SPEED);
    } else {
        m_player->setSpeed(0);
    }

    if (glfwGetKey(m_window, GLFW_KEY_A)) {
        m_player->setTurnSpeed(Player::MAX_TURN_SPEED);
    } else if (glfwGetKey(m_window, GLFW_KEY_D)) {
        m_player->setTurnSpeed(-Player::MAX_TURN_SPEED);
    } else {
        m_player->setTurnSpeed(0);
    }

    if (glfwGetKey(m_window, GLFW_KEY_Q)) {
        m_player->moveLeft();
    } else if (glfwGetKey(m_window, GLFW_KEY_E)) {
        m_player->moveRight();
    }

    if (glfwGetKey(m_window, GLFW_KEY_SPACE)) {
        m_player->jump();
    }

    static bool wasPressed = false;
    if (glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS) {
        wasPressed = true;
    }
    if (glfwGetKey(m_window, GLFW_KEY_C) == GLFW_RELEASE && wasPressed) {
        wasPressed = false;
        m_master->togglePhotoView(m_camera);
        m_gui->togglePhotoView();
    }
}

void GameWorld::pollMouse() const {

    double xPos, yPos;
    glfwGetCursorPos(m_window, &xPos, &yPos);

    int height, width;
    glfwGetWindowSize(m_window, &width, &height);

    if (xPos < 0 || xPos > width || yPos < 0 || yPos > height) return;

    // Temporary code for creating terrain
    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT)) {
        glm::vec3 ray = MousePicking::getWorldPosOfMouse(xPos,
                                                         yPos,
                                                         width,
                                                         height,
                                                         m_master->getProjectionMatrix(),
                                                         createViewMatrix(*m_camera));
        float     distance;
        glm::intersectRayPlane(m_camera->getPos(), ray, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), distance);
        glm::vec3 point = m_camera->getPos() + distance * ray;
        std::cout << std::fixed << std::setprecision(0) << point.x << " " << point.z << std::endl;
    }

    double yaw   = width / 2. - xPos;
    double pitch = height / 2. - yPos;

    float changedPitch = Camera::DEFAULT_PITCH + ((float) pitch * 0.1f);

    if (changedPitch > 0) {
        m_camera->setPitch(changedPitch);
    }
    m_camera->setAngleAroundPlayer((float) yaw * 0.1f);
}
