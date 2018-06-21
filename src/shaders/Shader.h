
#ifndef SAFARI_SHADER_H
#define SAFARI_SHADER_H


#include <string>
#include <unordered_map>
#include <glm/fwd.hpp>

class Shader {
private:
    unsigned int m_shaderId;
    mutable std::unordered_map<std::string, int> m_uniformCache; // mutable because it's a memoiziation caches

protected:
    int getUniformLocation(const std::string& name) const;

public:
    Shader(const std::string& vertex, const std::string& fragment);

    virtual ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;

    void setUniform1i(const std::string& name, int v) const;

    void setUniform1f(const std::string &name, float v) const;

    void setUniform3f(const std::string &name, glm::vec3 vec3) const;

    void setUniformMatrix4(const std::string &name, glm::mat4 mat) const;

    void setProjectionMatrix(const glm::mat4 matrix) const;
};


#endif //SAFARI_SHADER_H
