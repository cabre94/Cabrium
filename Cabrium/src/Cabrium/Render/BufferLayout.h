#pragma once

#include "Cabrium/Common/Assert.h"

#include <cstdint>
#include <string>
#include <vector>

namespace cabrium {

enum class ShaderDataType : uint32_t {
    None = 0,
    Vec1,
    Vec2,
    Vec3,
    Vec4,

    Mat3, // 3x3 float matrix
    Mat4, // 4x4 float matrix

    Int1,
    Int2,
    Int3,
    Int4,

    Bool,

};

struct BufferElement {
    std::string name;
    ShaderDataType type;
    uint32_t sz;
    // uint32_t offset;
    uint64_t offset;
    uint32_t cnt;

    // bool normalized;
    bool normalized; // TODO: bool?

    BufferElement() {} // ¿?

    BufferElement(ShaderDataType type_, const std::string name_, bool normalized_ = false)
        : type(type_),
          name(name_),
          sz(shaderDataTypeSz8(type_)),
          offset(0),
          cnt(shaderDataTypeCount(type_)),
          normalized(normalized_) {}

    static uint32_t shaderDataTypeSz8(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Vec1: return sizeof(float);
            case ShaderDataType::Vec2: return sizeof(float) * 2;
            case ShaderDataType::Vec3: return sizeof(float) * 3;
            case ShaderDataType::Vec4: return sizeof(float) * 4;

            case ShaderDataType::Mat3: return sizeof(float) * 3 * 3;
            case ShaderDataType::Mat4: return sizeof(float) * 4 * 4;

            case ShaderDataType::Int1: return sizeof(int); // FIXME? uint32_t/int32_t?
            case ShaderDataType::Int2: return sizeof(int) * 2;
            case ShaderDataType::Int3: return sizeof(int) * 3;
            case ShaderDataType::Int4: return sizeof(int) * 4;

            case ShaderDataType::Bool: return 1;

            case ShaderDataType::None:

            default: CBRM_CORE_ASSERT(false, "BufferElement::getTypeSz8 - invalid ShaderDataType")
        }

        return 0;

        // throw std::invalid_argument("invalid getTypeSz8");
    }

    static uint32_t shaderDataTypeCount(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Vec1: return 1;
            case ShaderDataType::Vec2: return 2;
            case ShaderDataType::Vec3: return 3;
            case ShaderDataType::Vec4: return 4;

            case ShaderDataType::Mat3: return 3 * 3;
            case ShaderDataType::Mat4: return 4 * 4;

            case ShaderDataType::Int1: return 1; // FIXME? uint32_t/int32_t?
            case ShaderDataType::Int2: return 2;
            case ShaderDataType::Int3: return 3;
            case ShaderDataType::Int4: return 4;

            case ShaderDataType::Bool: return 1;

            case ShaderDataType::None:

            default: CBRM_CORE_ASSERT(false, "BufferElement::getCount - invalid ShaderDataType")
        }

        return 0;

        // throw std::invalid_argument("invalid getTypeSz8");
    }

    uint32_t getCount() const { return cnt; }
};

class BufferLayout {
public:
    BufferLayout(const std::initializer_list<BufferElement> &elements_ = {})
        : stride(0), elements(elements_) {
        updateParams();
    }

    // BufferLayout() {} // ¿?

    ~BufferLayout() {}

    //    BufferLayout() : stride(0) {}
    //~BufferLayout() {}

    // template<typename T>
    // void push(uint32_t count) {
    //     static_assert(false);
    // }

    // template<>
    // void push<float>(uint32_t cnt) {
    //     elements.push_back({GL_FLOAT, cnt, GL_FALSE});
    //     stride += cnt * BufferElement::getTypeSz8(GL_FLOAT);
    // }

    // template<>
    // void push<uint32_t>(uint32_t cnt) {
    //     elements.push_back({GL_UNSIGNED_INT, cnt, GL_FALSE});
    //     stride += cnt * BufferElement::getTypeSz8(GL_UNSIGNED_INT);
    // }

    // template<>
    // void push<uint8_t>(uint32_t cnt) {
    //     elements.push_back({GL_UNSIGNED_BYTE, cnt, GL_TRUE});
    //     // elements.emplace_back
    //     stride += cnt * BufferElement::getTypeSz8(GL_UNSIGNED_BYTE);
    // }

    const std::vector<BufferElement> &getElements() const { return elements; }
    // uint32_t getStride() const { return stride; }

    // iterators
    std::vector<BufferElement>::iterator begin() { return elements.begin(); }
    std::vector<BufferElement>::iterator end() { return elements.end(); }
    std::vector<BufferElement>::reverse_iterator rbegin() { return elements.rbegin(); }
    std::vector<BufferElement>::reverse_iterator rend() { return elements.rend(); }

    // const iterators
    std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return elements.end(); }
    std::reverse_iterator<std::vector<BufferElement>::const_iterator> rbegin() const {
        return elements.rbegin();
    }
    std::reverse_iterator<std::vector<BufferElement>::const_iterator> rend() const {
        return elements.rend();
    }

    uint32_t getStride() const { return stride; }

private:
    void updateParams() {
        stride = 0;

        for (BufferElement &element : elements) {
            element.offset = stride;
            stride += element.sz;
        }
    }

    uint32_t stride;
    std::vector<BufferElement> elements;
};

} // namespace cabrium