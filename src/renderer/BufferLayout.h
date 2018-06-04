
#ifndef SAFARI_BUFFERLAYOUT_H
#define SAFARI_BUFFERLAYOUT_H

#include <vector>
#include <GL/glew.h>
#include "../util/GL.h"

struct LayoutElements {
    unsigned int count;
    unsigned int type;
    unsigned char normalized;

    LayoutElements(unsigned int type, unsigned int count, unsigned char normalized) : count(count),
                                                                             type(type),
                                                                             normalized(normalized) {}
};

class BufferLayout {
private:
    std::vector<LayoutElements> m_elements;
    unsigned int                m_stride;
public:
    BufferLayout() : m_stride(0) {}

    void push(unsigned int type, unsigned int count, unsigned char normalized) {
        m_elements.push_back(LayoutElements(type, count, normalized));
        m_stride += count * GL::typeToSizeOf(type);
    }

    void pushFloat(unsigned int count) {
        push(GL_FLOAT, count, GL_FALSE);
    }

    void pushUInt(unsigned int count) {
        push(GL_UNSIGNED_INT, count, GL_FALSE);
    }

    const std::vector<LayoutElements> getElements() const { return m_elements; }

    unsigned int getStride() const { return m_stride; }
};


#endif //SAFARI_BUFFERLAYOUT_H
