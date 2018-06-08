
#ifndef SAFARI_SHADER_H
#define SAFARI_SHADER_H


#include <string>
#include <unordered_map>
#include <glm/fwd.hpp>

class Shader {
private:
    unsigned int m_shaderId;
    std::unordered_map<std::string, int> m_uniformCache;

protected:
    int getUniformLocation(const std::string& name);

public:
    Shader(const std::string& vertex, const std::string& fragment);

    virtual ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

    void setUniform1i(const std::string& name, int v);

    void setUniform3f(const std::string &name, glm::vec3 vec3);

    void setUniformMatrix4(const std::string &name, glm::mat4 mat);
};


#endif //SAFARI_SHADER_H
