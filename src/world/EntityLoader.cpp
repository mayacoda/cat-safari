
#include "EntityLoader.h"

void
EntityLoader::loadTerrain(const std::string &configPath, std::vector<Entity*> &entities, std::vector<Model*> &models) {
    std::ifstream inFile(configPath);
    if (!inFile.is_open()) {
        throw std::runtime_error("[EntityLoader:loadTerrain]: Unable to open file: " + configPath);
    }

    std::map<std::string, TexturedModel*> modelMap;
    std::string line;

    while(std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string model, texture;
        int x, z;
        float yRot;
        float scale;

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

void EntityLoader::loadCats(std::vector<Entity*> &entities, std::vector<Model*> &models) {
    TexturedModel* cat1 = loadObjModel("cat", "cat_tex1");
    TexturedModel* cat2 = loadObjModel("cat", "cat_tex2");

    models.push_back(cat1);
    models.push_back(cat2);

    for (int i = 0; i < 20; i++) {
        entities.push_back(new Entity(cat1, glm::vec3(iRandomRange(0, 200) - 100, 0, iRandomRange(0, 200) - 100), glm::vec3(0,iRandomRange(0, 360),0), 1));
    }

    for (int i = 0; i < 20; i++) {
        entities.push_back(new Entity(cat2, glm::vec3(iRandomRange(0, 200) - 100, 0, iRandomRange(0, 200) - 100), glm::vec3(0,iRandomRange(0, 360),0), 1));
    }
}
