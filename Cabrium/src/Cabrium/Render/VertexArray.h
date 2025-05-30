#pragma once

#include "Cabrium/Common/Types.h"
#include "Cabrium/Render/BufferLayout.h"
#include "Cabrium/Render/Buffers.h"

namespace cabrium {

class IVertexArray {
public:
    // IVertexArray();
    virtual ~IVertexArray() {};

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    virtual void addBuffer(const Ref<IVertexBuffer> &v_buff)     = 0;
    virtual void setIndexBuffer(const Ref<IIndexBuffer> &i_buff) = 0;

    // void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const;

    virtual const std::vector<Ref<IVertexBuffer>> &getVextexBuffers() const = 0;
    virtual const Ref<IIndexBuffer> &getIndexBuffer() const                 = 0;

    static IVertexArray *create();
};

} // namespace cabrium