
#include "MasterRenderer.h"


MasterRenderer::MasterRenderer(int width, int height) : m_width(width), m_height(height) {
    init();
    m_projectionMatrix = Geometry::createProjectionMatrix(width, height);

    m_entityShader   = new StaticShader();
    m_entityRenderer = new EntityRenderer(m_entityShader, m_projectionMatrix);

    m_terrainShader   = new TerrainShader();
    m_terrainRenderer = new TerrainRenderer(m_terrainShader, m_projectionMatrix);

    m_guiRenderer = new GUIRenderer();
}

MasterRenderer::~MasterRenderer() {
    delete m_entityShader;
    delete m_entityRenderer;

    delete m_terrainShader;
    delete m_terrainRenderer;

    delete m_guiRenderer;
}

void MasterRenderer::render(const Light &light, const Camera &camera, const GUI &gui) {

    glm::vec3 skyColor(0.6, 0.8, 0.9);
    debug(glClearColor(skyColor.r, skyColor.g, skyColor.b, 1));
    debug(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    m_entityShader->bind();
    m_entityShader->loadLight(light);
    m_entityShader->loadViewMatrix(camera);
    m_entityShader->loadSkyColor(skyColor);

    m_entityRenderer->render(m_entities);

    m_entityShader->unbind();

    m_terrainShader->bind();
    m_terrainShader->loadLight(light);
    m_terrainShader->loadViewMatrix(camera);
    m_terrainShader->loadSkyColor(skyColor);
    m_terrainShader->loadProjectionMatrix(m_projectionMatrix);

    m_terrainRenderer->render(m_terrains);
    m_terrainShader->unbind();

    m_guiRenderer->render(gui.getTextures());

    m_entities.clear();
    m_terrains.clear();
}

void MasterRenderer::processEntity(Entity* entity) {
    const TexturedModel* model = entity->getModel();

    if (m_entities.find(model) != m_entities.end()) {
        m_entities[model].push_back(entity);
    } else {
        m_entities[model] = std::list<Entity*>();
        m_entities[model].push_back(entity);
    }
}

void MasterRenderer::cleanUp() {

    for (auto it = m_entities.begin(); it != m_entities.end(); it++) {
        const TexturedModel* const model = it->first;
        model->unbind();
    }

    m_entityShader->unbind();
    m_terrainShader->unbind();
}

void MasterRenderer::init() {
    debug(glEnable(GL_DEPTH_TEST));
    debug(glEnable(GL_BLEND));
    MasterRenderer::enableCulling();
    debug(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void MasterRenderer::processTerrain(Terrain* terrain) {
    m_terrains.push_back(terrain);
}

void MasterRenderer::togglePhotoView(Camera* camera) {
    camera->togglePhotoView();

    if (camera->isInPhotoView()) {
        m_projectionMatrix = Geometry::createPhotoViewProjectionMatrix(m_width, m_height);
    } else {
        m_projectionMatrix = Geometry::createProjectionMatrix(m_width, m_height);
    }

    m_entityShader->bind();
    m_entityShader->loadProjectionMatrix(m_projectionMatrix);
    m_entityShader->unbind();

    m_terrainShader->bind();
    m_terrainShader->loadProjectionMatrix(m_projectionMatrix);
    m_terrainShader->unbind();
}
