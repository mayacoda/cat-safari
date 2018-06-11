
#ifndef SAFARI_BUFFERLAYOUT_H
#define SAFARI_BUFFERLAYOUT_H

#include <vector>
#include <GL/glew.h>
#include "../util/GL.h"

struct LayoutElements {
    unsigned int  count;
    unsigned int  type;
    unsigned char normalized;
    const char* name;

    LayoutElements(unsigned int type, unsigned int count, unsigned char normalized, const char* name) : count(count),
                                                                                                  type(type),
                                                                                                  normalized(normalized),
                                                                                                  name(name) {}
};

class BufferLayout {
private:
    std::vector<LayoutElements> m_elements;
    unsigned int                m_stride;
public:
    BufferLayout() : m_stride(0) {}

    void push(unsigned int type, unsigned int count, unsigned char normalized, const std::string &name);

    void pushFloat(unsigned int count,const std::string& name = "");

    void pushUInt(unsigned int count,const std::string& name = "");

    const std::vector<LayoutElements> getElements() const { return m_elements; }

    unsigned int getStride() const { return m_stride; }
};


#endif //SAFARI_BUFFERLAYOUT_H
