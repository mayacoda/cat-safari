
#include "BufferLayout.h"

void BufferLayout::push(unsigned int type, unsigned int count, unsigned char normalized, const std::string &name) {
    m_elements.push_back(LayoutElements(type, count, normalized, !name.empty() ? name.c_str() : 0));
    m_stride += count * GL::typeToSizeOf(type);
}

void BufferLayout::pushFloat(unsigned int count, const std::string &name) {
    push(GL_FLOAT, count, GL_FALSE, name);
}

void BufferLayout::pushUInt(unsigned int count, const std::string &name) {
    push(GL_UNSIGNED_INT, count, GL_FALSE, name);
}
