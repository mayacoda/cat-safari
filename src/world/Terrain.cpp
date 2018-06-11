
#include "Terrain.h"

TexturedModel* Terrain::generateTerrain() {

    int count = Terrain::VERTEX_COUNT * Terrain::VERTEX_COUNT;
    auto* vertices = new float[count * 8];
    auto* indices  = new unsigned int[6 * (Terrain::VERTEX_COUNT - 1) * (Terrain::VERTEX_COUNT - 1)];

    int vertexPointer = 0;

    for (int i = 0; i < Terrain::VERTEX_COUNT; i++) {

        for (int j = 0; j < Terrain::VERTEX_COUNT; j++) {

            vertices[vertexPointer]     = (float) j / ((float) Terrain::VERTEX_COUNT - 1) * SIZE;
            vertices[vertexPointer + 1] = 0;
            vertices[vertexPointer + 2] = (float) i / ((float) Terrain::VERTEX_COUNT - 1) * SIZE;

            vertices[vertexPointer + 3] = 0; // normal1
            vertices[vertexPointer + 4] = 1; // normal2
            vertices[vertexPointer + 5] = 0; // normal3

            // textures
            vertices[vertexPointer + 6] = (float) j / ((float) Terrain::VERTEX_COUNT - 1);
            vertices[vertexPointer + 7] = (float) i / ((float) Terrain::VERTEX_COUNT - 1);

            vertexPointer += 8;
        }
    }

    int pointer = 0;

    for (unsigned int gz = 0; gz < Terrain::VERTEX_COUNT - 1; gz++) {
        for (unsigned int gx = 0; gx < Terrain::VERTEX_COUNT - 1; gx++) {
            unsigned int topLeft     = (gz * Terrain::VERTEX_COUNT) + gx;
            unsigned int topRight    = topLeft + 1;
            unsigned int bottomLeft  = ((gz + 1) * Terrain::VERTEX_COUNT) + gx;
            unsigned int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }

    Texture* texture = new Texture("./res/textures/terrain2.png", true);

    auto* va = new VertexArray();
    auto* vb = new VertexBuffer(vertices, (unsigned int) count * 8 * sizeof(float));

    BufferLayout layout;
    layout.pushFloat(3, "position");
    layout.pushFloat(3, "normal");
    layout.pushFloat(2, "texture");
    va->addBuffer(*vb, layout);

    auto* ib = new IndexBuffer(indices,
                               (unsigned int) (6 * (Terrain::VERTEX_COUNT - 1) *
                                               (Terrain::VERTEX_COUNT - 1)));

    return new TexturedModel(va, ib, texture);
}
