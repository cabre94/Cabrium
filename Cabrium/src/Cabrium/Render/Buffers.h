#pragma once

#include "Cabrium/Render/BufferLayout.h"

#include <cstdint>

namespace cabrium {

class IVertexBuffer {
public:
    // VertexBuffer(const void *data, uint32_t sz);
    virtual ~IVertexBuffer() {}

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    virtual void setLayout(const BufferLayout &layout) = 0;
    virtual const BufferLayout &getLayout()            = 0;

    static IVertexBuffer *create(const void *data, uint32_t sz);
};

class IIndexBuffer {
public:
    // IndexBuffer(const uint32_t *data, uint32_t cnt);
    virtual ~IIndexBuffer() {}

    virtual void bind() const   = 0;
    virtual void unbind() const = 0;

    virtual uint32_t getIndexCnt() const = 0;

    static IIndexBuffer *create(const uint32_t *idx, uint32_t cnt);
};

} // namespace cabrium