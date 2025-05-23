#pragma once

#include "Cabrium/Render/BufferLayout.h"
#include "Cabrium/Render/Buffers.h"

namespace cabrium {

class IVertexArray {
public:
    // IVertexArray();
    virtual ~IVertexArray() {};

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    virtual void addBuffer(const std::shared_ptr<IVertexBuffer> &v_buff)     = 0;
    virtual void setIndexBuffer(const std::shared_ptr<IIndexBuffer> &i_buff) = 0;

    // void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const;

    virtual const std::vector<std::shared_ptr<IVertexBuffer>> &getVextexBuffers() const = 0;
    virtual const std::shared_ptr<IIndexBuffer> &getIndexBuffer() const                 = 0;

    static IVertexArray *create();
};

} // namespace cabrium