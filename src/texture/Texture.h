
#ifndef SAFARI_TEXTURE_H
#define SAFARI_TEXTURE_H


#include <string>

class Texture {
private:
    unsigned int m_textureId;
    std::string  m_filePath;
    unsigned char* m_buffer;
    int m_width, m_height, m_bpp;

    float m_shineDamper = 1;
    float m_reflectivity = 0;

public:
    Texture(const std::string &m_filePath);

    virtual ~Texture();

    float getShineDamper() const;

    float getReflectivity() const;

    void setShineDamper(float m_shineDamper);

    void setReflectivity(float m_reflectivity);

    void bind(unsigned int slot = 0) const;

    void unbind() const;

};


#endif //SAFARI_TEXTURE_H
