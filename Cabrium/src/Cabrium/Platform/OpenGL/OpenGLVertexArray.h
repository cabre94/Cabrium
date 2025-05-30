#pragma once

#include "Cabrium/Common/Types.h"
#include "Cabrium/Render/VertexArray.h"

#include <cstdint>

namespace cabrium {
namespace opengl {

class VertexArray : public IVertexArray {
public:
    VertexArray();
    virtual ~VertexArray();

    void bind() const override;
    void unbind() const override;

    void addBuffer(const Ref<IVertexBuffer> &v_buff);
    void setIndexBuffer(const Ref<IIndexBuffer> &i_buff);

    const std::vector<Ref<IVertexBuffer>> &getVextexBuffers() const;
    const Ref<IIndexBuffer> &getIndexBuffer() const;

private:
    std::vector<Ref<IVertexBuffer>> vertex_buff;
    Ref<IIndexBuffer> index_buff;

    uint32_t render_id;
};

} // namespace opengl
} // namespace cabrium