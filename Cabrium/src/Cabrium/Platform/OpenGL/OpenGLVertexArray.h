#pragma once

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

    void addBuffer(const std::shared_ptr<IVertexBuffer> &v_buff);
    void setIndexBuffer(const std::shared_ptr<IIndexBuffer> &i_buff);

    const std::vector<std::shared_ptr<IVertexBuffer>> &getVextexBuffers() const;
    const std::shared_ptr<IIndexBuffer> &getIndexBuffer() const;

private:
    std::vector<std::shared_ptr<IVertexBuffer>> vertex_buff;
    std::shared_ptr<IIndexBuffer> index_buff;

    uint32_t render_id;
};

} // namespace opengl
} // namespace cabrium