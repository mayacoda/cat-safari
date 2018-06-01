
#ifndef SAFARI_VERTEXBUFFER_H
#define SAFARI_VERTEXBUFFER_H


class VertexBuffer {
private:
    unsigned int m_vboId;
public:
    VertexBuffer(const void* data, unsigned int size);

    ~VertexBuffer();

    void bind() const;

    void unbind() const;

};


#endif //SAFARI_VERTEXBUFFER_H
