
#ifndef SAFARI_FILEUTILITY_H
#define SAFARI_FILEUTILITY_H


#include <string>
#include "../models/Model.h"
#include "../models/TexturedModel.h"

std::string getFileContents(const std::string& filePath);

TexturedModel* loadObjModel(const std::string& filePath);

TexturedModel* loadObjModel(const std::string& modelPath, const std::string& texturePath);



#endif //SAFARI_FILEUTILITY_H
