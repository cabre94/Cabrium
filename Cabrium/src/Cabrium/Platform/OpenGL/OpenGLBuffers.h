#pragma once

#include "Cabrium/Render/BufferLayout.h"
#include "Cabrium/Render/Buffers.h"

namespace cabrium {

namespace opengl {

class VertexBuffer : public IVertexBuffer {
public:
    VertexBuffer(const void *data, uint32_t sz);
    virtual ~VertexBuffer();

    void bind() const override;
    void unbind() const override;

    void setLayout(const BufferLayout &layout) override { buff_layout = layout; }
    const BufferLayout &getLayout() override { return buff_layout; }

private:
    uint32_t render_id;

    BufferLayout buff_layout;
};

class IndexBuffer : public IIndexBuffer {
public:
    IndexBuffer(const uint32_t *data, uint32_t cnt);
    virtual ~IndexBuffer();

    void bind() const override;
    void unbind() const override;

    uint32_t getIndexCnt() const override;

private:
    uint32_t render_id;
    uint32_t idx_cnt;
};

} // namespace opengl

} // namespace cabrium
