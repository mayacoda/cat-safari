
#include <glm/gtx/rotate_vector.hpp>
#include "EntityLoader.h"

void
EntityLoader::loadTerrain(const std::string &configPath, std::vector<Entity*> &entities, std::vector<Model*> &models) {
    std::ifstream inFile(configPath);
    if (!inFile.is_open()) {
        throw std::runtime_error("[EntityLoader:loadTerrain]: Unable to open file: " + configPath);
    }

    std::map<std::string, TexturedModel*> modelMap;
    std::string                           line;

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string        model, texture;
        int                x, z;
        float              yRot;
        float              scale;

        iss >> model >> texture >> x >> z >> yRot >> scale;

        if (model.find('#') == 0) continue;

        const std::string &key = model + texture;
        TexturedModel* m;

        if (!modelMap.count(key)) {
            std::cout << "creating model: " << key << std::endl;
            m = loadObjModel(model, texture);
            modelMap[key] = m;
            models.push_back(m);
        } else {
            m = modelMap.find(key)->second;
        }

        Entity* e = new Entity(m, glm::vec3(x, 0, z), glm::vec3(0, yRot, 0), scale);

        entities.push_back(e);
    }

    modelMap.clear();
}

bool canPlaceCat(float x, float z, std::vector<Entity*> &obstacles) {
    bool canPlace = true;

    for (auto it = obstacles.begin(); it != obstacles.end(); it++) {
        auto box    = (*it)->getModel()->getBoundingBox();
        auto origin = (*it)->getModel()->getOrigin();
        auto pos    = (*it)->getPos();
        auto scale  = (*it)->getScale();
        auto yRot  = (*it)->getRotation().y;

        auto maxFromOriginScaled = (origin - box.points[0]) * scale * 1.01f;
        auto minFromOriginScaled = (origin - box.points[7]) * scale * 1.01f;
        maxFromOriginScaled = glm::rotateY(maxFromOriginScaled, yRot);
        minFromOriginScaled = glm::rotateY(maxFromOriginScaled, yRot);

        float maxX = maxFromOriginScaled.x + pos.x - origin.x;
        float maxZ = maxFromOriginScaled.z + pos.z - origin.z;
        float minX = minFromOriginScaled.x + pos.x - origin.x;
        float minZ = minFromOriginScaled.z + pos.z - origin.z;

        if (x <= maxX && x >= minX && z <= maxZ && z >= minZ) {
            canPlace = false;
        }
    }

    return canPlace;
}


glm::vec3 randomValidLocation(std::vector<Entity*> &obstacles) {
    float x = 0, z = 0;
    do {
        x = fRandomRange(0, 600) - 300;
        z = fRandomRange(0, 600) - 300;
    } while (!canPlaceCat(x, z, obstacles));

    return glm::vec3(x, 0, z);
}

void
EntityLoader::loadCats(std::vector<Entity*> &entities, std::vector<Entity*> &obstacles, std::vector<Model*> &models) {
    TexturedModel* cat1 = loadObjModel("cat", "cat_tex1");
    TexturedModel* cat2 = loadObjModel("cat", "cat_tex2");

    models.push_back(cat1);
    models.push_back(cat2);

    for (int i = 0; i < 10; i++) {
        entities.push_back(new Entity(cat1, randomValidLocation(obstacles), glm::vec3(0, iRandomRange(0, 360), 0), 1));
    }

    for (int i = 0; i < 10; i++) {
        entities.push_back(new Entity(cat2, randomValidLocation(obstacles), glm::vec3(0, iRandomRange(0, 360), 0), 1));
    }
}
