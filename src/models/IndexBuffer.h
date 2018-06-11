
#ifndef SAFARI_INDEXBUFFER_H
#define SAFARI_INDEXBUFFER_H


#include "../util/NonCopyable.h"

class IndexBuffer {
private:
    unsigned int m_iboId;
    unsigned int m_count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);

    ~IndexBuffer();

    void bind() const;

    void unbind() const;

    unsigned int getId() const { return m_iboId; }

    unsigned int getCount() const { return m_count; }

};


#endif //SAFARI_INDEXBUFFER_H
