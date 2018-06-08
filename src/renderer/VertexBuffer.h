
#ifndef SAFARI_VERTEXBUFFER_H
#define SAFARI_VERTEXBUFFER_H


class VertexBuffer {
private:
    unsigned int m_vboId;
public:
    /**
     *
     * @param data raw data, the actual array
     * @param size
     */
    VertexBuffer(const void* data, unsigned int size);

    ~VertexBuffer();

    void bind() const;

    void unbind() const;

};


#endif //SAFARI_VERTEXBUFFER_H
