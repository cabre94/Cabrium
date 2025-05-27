#include "cbrm_pch.h"

#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace cabrium {

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : proj_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), view_matrix(1.0f), pos{} {
    view_proj_matrix = proj_matrix * view_matrix;
}

void OrthographicCamera::update() {
    // TODO: Check performance and readability
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *
                          // glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 0, 1));
                          glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));

    view_matrix = glm::inverse(transform);

    view_proj_matrix = proj_matrix * view_matrix;
}

} // namespace cabrium