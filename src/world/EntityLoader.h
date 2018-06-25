
#ifndef SAFARI_ENTITYLOADER_H
#define SAFARI_ENTITYLOADER_H


#include <fstream>
#include <map>
#include <sstream>
#include "Entity.h"
#include "../util/fileUtil.h"
#include "../util/helpers.h"

namespace EntityLoader {
    void loadTerrain(const std::string &configPath,
                            std::vector<Entity*> &entities,
                            std::vector<Model*> &models);

    void loadCats(std::vector<Entity*> &entities, std::vector<Entity*> &obstacles, std::vector<Model*> &models);
};


#endif //SAFARI_ENTITYLOADER_H
