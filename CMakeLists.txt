cmake_minimum_required(VERSION 3.9)
project(safari)

set(CMAKE_CXX_STANDARD 11)

add_executable(safari
        src/main.cpp
        src/util/fileUtil.cpp
        src/util/GL.cpp
        src/renderer/VertexBuffer.cpp
        src/renderer/IndexBuffer.cpp
        src/renderer/VertexArray.cpp
        src/renderer/BufferLayout.cpp
        src/renderer/Renderer.cpp
        src/shaders/shaderLoader.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_library(GLEW_LIBRARIES NAMES glew64 GLEW glew glew32 /usr/local/lib)
find_library(GLFW_LIBRARY NAMES glfw3 glfw /usr/local/lib)

link_directories(/usr/local/lib)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} /usr/local/include)

target_link_libraries(safari ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${GLFW_LIBRARY})