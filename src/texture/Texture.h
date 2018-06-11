
#ifndef SAFARI_TEXTURE_H
#define SAFARI_TEXTURE_H


#include <string>
#include "../util/NonCopyable.h"

class Texture {
private:
    unsigned int m_textureId;
    std::string  m_filePath;
    unsigned char* m_buffer;
    int m_width, m_height, m_bpp;

    bool m_hasTransparency;

    float m_shineDamper = 1;
    float m_reflectivity = 0;

public:
    Texture(const std::string &m_filePath, bool tile = false);

    ~Texture();

    float getShineDamper() const;

    float getReflectivity() const;

    void setShineDamper(float m_shineDamper);

    void setReflectivity(float m_reflectivity);

    unsigned int getId() const { return m_textureId; }

    bool getTransparency() const { return m_hasTransparency; }

    void bind(unsigned int slot = 0) const;

    void unbind() const;

};


#endif //SAFARI_TEXTURE_H
