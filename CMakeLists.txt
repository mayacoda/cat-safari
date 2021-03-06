cmake_minimum_required(VERSION 3.9)
project(safari)

set(CMAKE_CXX_STANDARD 98)

add_executable(safari
        src/main.cpp
        lib/stb_image.cpp
        lib/glm.h
        src/models/Model.cpp
        src/models/TexturedModel.cpp
        src/models/VertexBuffer.cpp
        src/models/IndexBuffer.cpp
        src/models/VertexArray.cpp
        src/models/BufferLayout.cpp
        src/renderer/MasterRenderer.cpp
        src/renderer/EntityRenderer.cpp
        src/shaders/StaticShader.cpp
        src/shaders/shaderLoader.cpp
        src/shaders/Shader.cpp
        src/texture/Texture.cpp
        src/util/fileUtil.cpp
        src/util/GL.cpp
        src/util/geometry.cpp
        src/world/Camera.cpp
        src/world/Entity.cpp
        src/world/Light.cpp
        src/world/GameWorld.cpp src/world/Terrain.cpp src/world/Terrain.h src/shaders/TerrainShader.cpp src/shaders/TerrainShader.h src/renderer/TerrainRenderer.cpp src/renderer/TerrainRenderer.h src/texture/TerrainTexture.cpp src/texture/TerrainTexture.h src/texture/TerrainTexturePack.cpp src/texture/TerrainTexturePack.h src/world/Player.cpp src/world/Player.h src/util/helpers.h src/world/GUI.cpp src/world/GUI.h src/renderer/GUIRenderer.cpp src/renderer/GUIRenderer.h src/shaders/GUIShader.cpp src/shaders/GUIShader.h src/texture/GUITexture.cpp src/texture/GUITexture.h src/world/EntityLoader.cpp src/world/EntityLoader.h src/util/mouse-picking.h src/util/Frustum.cpp src/util/Frustum.h src/util/Collisions.cpp src/util/Collisions.h src/util/Hexahedron.cpp src/util/Hexahedron.h src/util/Plane.cpp src/util/Plane.h src/world/GameState.cpp src/world/GameState.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_library(GLEW_LIBRARIES NAMES glew64 GLEW glew glew32 /usr/local/lib)
find_library(GLFW_LIBRARY NAMES glfw3 glfw /usr/local/lib)

link_directories(/usr/local/lib)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} /usr/local/include)

target_link_libraries(safari ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${GLFW_LIBRARY})