#pragma once

#include <glm/glm.hpp>

namespace cabrium {

class OrthographicCamera {
public:
    // TODO: add constructor with projection matrix
    OrthographicCamera(float left, float right, float bottom, float top);

    const glm::vec3 &getPosition() const { return pos; };
    void setPosition(const glm::vec3 &pos_) {
        pos = pos_;
        update();
    }

    float getRotation() const { return rotation; }
    void setRotation(float rotation_) {
        rotation = rotation_;
        update();
    }

    const glm::mat4 &getProjectionMatrix() const { return proj_matrix; }
    const glm::mat4 &getViewMatrix() const { return view_matrix; }
    const glm::mat4 &getViewProjectionMatrix() const { return view_proj_matrix; }

    // const void setProjectionMatrix(const glm::mat4 &proj_matrix_) { proj_matrix = proj_matrix_; }
    // const void setviewMatrix(const glm::mat4 &proj_matrix_) { proj_matrix = proj_matrix_; }

private:
    void update();

    glm::mat4 proj_matrix;
    glm::mat4 view_matrix; // inverse of transformation matrix?
    glm::mat4 view_proj_matrix;

    glm::vec3 pos;
    float rotation = 0.0f;
};

} // namespace cabrium
