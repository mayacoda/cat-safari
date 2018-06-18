
#include <glm/glm.hpp>
#include "../util/fileUtil.h"
#include "GameWorld.h"
#include "../util/helpers.h"

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
}

void GameWorld::init(GLFWwindow* window) {
    m_window = window;
    m_light  = new Light(glm::vec3(0, 100, -20), glm::vec3(1, 1, 1));

    int width, height;
    glfwGetWindowSize(m_window, &width, &height);

    m_master = new MasterRenderer(width, height);

    TexturedModel* player = loadObjModel("player");
    TexturedModel* tree1 = loadObjModel("tree1");
    TexturedModel* cat1 = loadObjModel("cat", "cat_tex1");
    TexturedModel* cat2 = loadObjModel("cat", "cat_tex2");
    m_player = new Player(player, glm::vec3(0, 0, 0), glm::vec3(0), 1);
    m_camera = new Camera(m_player);

    m_entities.push_back(m_player);

    for (int i = 0; i < 20; i++) {
        m_entities.push_back(new Entity(tree1, glm::vec3(iRandomRange(0, 200) - 100, 0, iRandomRange(0, 200) - 100), glm::vec3(0,iRandomRange(0, 360),0), fRandomRange(0.5f, 2)));
    }

    for (int i = 0; i < 20; i++) {
        m_entities.push_back(new Entity(cat1, glm::vec3(iRandomRange(0, 200) - 100, 0, iRandomRange(0, 200) - 100), glm::vec3(0,iRandomRange(0, 360),0), 1));
    }


    for (int i = 0; i < 20; i++) {
        m_entities.push_back(new Entity(cat2, glm::vec3(iRandomRange(0, 200) - 100, 0, iRandomRange(0, 200) - 100), glm::vec3(0,iRandomRange(0, 360),0), 1));
    }


    m_models.push_back(player);
    m_models.push_back(cat1);
    m_models.push_back(tree1);

    m_terrains.push_back(new Terrain(0, 0));
    m_terrains.push_back(new Terrain(1, 0));
    m_terrains.push_back(new Terrain(-1, 0));
    m_terrains.push_back(new Terrain(0, 1));
    m_terrains.push_back(new Terrain(1, 1));
    m_terrains.push_back(new Terrain(-1, 1));
    m_terrains.push_back(new Terrain(0, -1));
    m_terrains.push_back(new Terrain(1, -1));
    m_terrains.push_back(new Terrain(-1, -1));
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

    m_master->render(*m_light, *m_camera);
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

    if (glfwGetKey(m_window, GLFW_KEY_SPACE)) {
        m_player->jump();
    }
}

void GameWorld::pollMouse() const {
    double xPos, yPos;
    glfwGetCursorPos(m_window, &xPos, &yPos);

    int height, width;
    glfwGetWindowSize(m_window, &width, &height);

    double yaw   = width / 2. - xPos;
    double pitch = height / 2. - yPos;

    float changedPitch = Camera::DEFAULT_PITCH + ((float) pitch * 0.1f);

    if (changedPitch > 0) {
        m_camera->setPitch(changedPitch);
    }
    m_camera->setAngleAroundPlayer((float) yaw * 0.1f);
}
