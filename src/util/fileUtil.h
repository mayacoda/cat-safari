
#ifndef SAFARI_FILEUTILITY_H
#define SAFARI_FILEUTILITY_H


#include <string>
#include "../models/Model.h"
#include "../models/TexturedModel.h"

std::string getFileContents(const std::string& filePath);

TexturedModel* loadObjModel(const std::string& filePath);

void processVertex(const std::string &vertexData,
                   std::vector<unsigned int> &indices,
                   std::vector<glm::vec3> vertices,
                   std::vector<glm::vec2> textures,
                   std::vector<glm::vec3> normals,
                   float bufferData[]);

#endif //SAFARI_FILEUTILITY_H
