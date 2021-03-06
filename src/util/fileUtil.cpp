#include "fileUtil.h"

#include <fstream>
#include <sstream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <limits>
#include <algorithm>

void processVertex(const std::string &vertexData,
                   std::vector<unsigned int> &indices,
                   std::vector<glm::vec3> vertices,
                   std::vector<glm::vec2> textures,
                   std::vector<glm::vec3> normals,
                   float bufferData[]);

std::string getFileContents(const std::string &filePath) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    std::stringstream stream;
    stream << inFile.rdbuf();
    return stream.str();
} 

TexturedModel* loadObjModel(const std::string &modelPath, const std::string &texturePath) {
    std::ifstream inFile("./res/models/" + modelPath + ".obj");
    if (!inFile.is_open()) {
        throw std::runtime_error("[loadObjModel]: Unable to OBJ file: " + modelPath);
    }

    bool shouldInitializeVertices = true;

    std::string               line;
    std::vector<glm::vec3>    vertices;
    std::vector<glm::vec2>    textures;
    std::vector<glm::vec3>    normals;
    std::vector<unsigned int> indices;

    auto tmpNaN = std::numeric_limits<float>::infinity();
    float maxX = tmpNaN, maxY = tmpNaN, maxZ = tmpNaN;
    float minX = tmpNaN, minY = tmpNaN, minZ = tmpNaN;

    float* bufferData = nullptr;

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string        prefix;
        iss >> prefix;

        // line is a vertex position
        if (prefix == "v") {
            float x, y, z;
            iss >> x >> y >> z;

            if (x < minX || minX == std::numeric_limits<float>::infinity()) minX = x;
            if (x > maxX || maxX == std::numeric_limits<float>::infinity()) maxX = x;
            if (y < minY || minY == std::numeric_limits<float>::infinity()) minY = y;
            if (y > maxY || maxY == std::numeric_limits<float>::infinity()) maxY = y;
            if (z < minZ || minZ == std::numeric_limits<float>::infinity()) minZ = z;
            if (z > maxZ || maxZ == std::numeric_limits<float>::infinity()) maxZ = z;

            vertices.push_back(glm::vec3(x, y, z));

            // line is a texture coordinate
        } else if (prefix == "vt") {
            float x, y;
            iss >> x >> y;

            textures.push_back(glm::vec2(x, y));

            // line is a vertex normal
        } else if (prefix == "vn") {

            float x, y, z;
            iss >> x >> y >> z;

            normals.push_back(glm::vec3(x, y, z));

            // line is face
        } else if (prefix == "f") {

            if (shouldInitializeVertices) {
                // going to merge vertices, textures and normals into one array
                // vertices.size() = number of vertices in total
                // sizeof(float) = the array each part of the vertex is a float
                // 8 = number of parts of the vertex: 3 floats position, 2 floats texture, 3 floats normal
                bufferData               = (float*) alloca(vertices.size() * sizeof(float) * 8);
                shouldInitializeVertices = false;

                if (vertices.empty()) {
                    throw std::runtime_error("[loadObjModel]: Model \"" + modelPath + "\" doesn't have vertices!");
                }

                if (textures.empty()) {
                    throw std::runtime_error("[loadObjModel]: Model \"" + modelPath + "\" doesn't have textures!");
                }

                if (normals.empty()) {
                    throw std::runtime_error("[loadObjModel]: Model \"" + modelPath + "\" doesn't have normals!");
                }


            }


            std::string vertex1, vertex2, vertex3;
            iss >> vertex1 >> vertex2 >> vertex3;

            processVertex(vertex1, indices, vertices, textures, normals, bufferData);
            processVertex(vertex2, indices, vertices, textures, normals, bufferData);
            processVertex(vertex3, indices, vertices, textures, normals, bufferData);

        }
    }

    inFile.close();

    auto* texture = new Texture("./res/textures/" + texturePath + ".png");

    auto* va = new VertexArray();
    auto* vb = new VertexBuffer(bufferData, (unsigned int) vertices.size() * sizeof(float) * 8);

    BufferLayout layout;
    layout.pushFloat(3, "position");
    layout.pushFloat(2, "textureCoords");
    layout.pushFloat(3, "normal");
    va->addBuffer(*vb, layout);

    auto* ib = new IndexBuffer(&indices[0], static_cast<unsigned int>(indices.size()));

    auto* model = new TexturedModel(va, ib, texture);

    float ox = (maxX - minX) / 2, oy = (maxY - minY) / 2, oz = (maxZ - minZ) / 2;

    model->setOrigin(glm::vec3(ox, oy, oz));
    model->setBoundingBox(minX, minY, minZ, maxX, maxY, maxZ);

    return model;
}

TexturedModel* loadObjModel(const std::string &fileName) {
    return loadObjModel(fileName, fileName);
}

void processVertex(const std::string &input,
                   std::vector<unsigned int> &indices,
                   std::vector<glm::vec3> vertices,
                   std::vector<glm::vec2> textures,
                   std::vector<glm::vec3> normals,
                   float bufferData[]) {

    // vertexData example
    // 41/1/1
    // vertexIndex / textureIndex / normalIndex
    std::string vertexData = input;
    std::replace(vertexData.begin(), vertexData.end(), '/', ' ');

    std::istringstream iss(vertexData);
    unsigned int       vertexIndex, textureIndex, normalIndex;
    iss >> vertexIndex >> textureIndex >> normalIndex;

    // decrement all indices by 1 because obj files are indexed from 1
    vertexIndex--;
    textureIndex--;
    normalIndex--;

    indices.push_back(vertexIndex);

    glm::vec3 vertex = vertices[vertexIndex];

    vertexIndex *= 8; // moveBy by 8 every time because there are 8 elements to each vertex
    bufferData[vertexIndex]     = vertex.x;
    bufferData[vertexIndex + 1] = vertex.y;
    bufferData[vertexIndex + 2] = vertex.z;

    glm::vec2 texture = textures[textureIndex];
    bufferData[vertexIndex + 3] = texture.x;
    bufferData[vertexIndex + 4] = texture.y; // obj files have inverted texture coordinates compared to OpenGL

    glm::vec3 normal = normals[normalIndex];
    bufferData[vertexIndex + 5] = normal.x;
    bufferData[vertexIndex + 6] = normal.y;
    bufferData[vertexIndex + 7] = normal.z;
}
