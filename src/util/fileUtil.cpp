#include "fileUtil.h"

#include <fstream>
#include <sstream>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

std::string getFileContents(const std::string &filePath) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    std::stringstream stream;
    stream << inFile.rdbuf();
    return stream.str();
}

TexturedModel* loadObjModel(const std::string &fileName) {
    std::ifstream inFile("./res/models/" + fileName + ".obj");
    if (!inFile.is_open()) {
        throw std::runtime_error("Unable to OBJ file: " + fileName);
    }

    bool shouldInitializeVertices = true;

    std::string               line;
    std::vector<glm::vec3>    vertices;
    std::vector<glm::vec2>    textures;
    std::vector<glm::vec3>    normals;
    std::vector<unsigned int> indices;

    float* bufferData = nullptr;

    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string        prefix;
        iss >> prefix;

        // line is a vertex position
        if (prefix == "v") {
            float x, y, z;
            iss >> x >> y >> z;

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
            }


            std::string vertex1, vertex2, vertex3;
            iss >> vertex1 >> vertex2 >> vertex3;

            processVertex(vertex1, indices, vertices, textures, normals, bufferData);
            processVertex(vertex2, indices, vertices, textures, normals, bufferData);
            processVertex(vertex3, indices, vertices, textures, normals, bufferData);

        }
    }

    inFile.close();

    auto* texture = new Texture("./res/textures/" + fileName + ".png");
    texture->bind();

    auto* va = new VertexArray();
    auto* vb = new VertexBuffer(bufferData, (unsigned int) vertices.size() * sizeof(float) * 8);

    BufferLayout layout;
    layout.pushFloat(3, "position");
    layout.pushFloat(2, "textureCoords");
    layout.pushFloat(3, "normal");
    va->addBuffer(*vb, layout);

    auto* ib = new IndexBuffer(&indices[0], static_cast<unsigned int>(indices.size() * sizeof(unsigned int)));

    auto* pointersModel = new TexturedModel(*va, *ib, *texture);

    return pointersModel;
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

    vertexIndex *= 8; // move by 8 every time because there are 8 elements to each vertex
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
