#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object.h"
#include "Shader.h"
#include "Texture.h"

class Cube : public Object {
public:
    Cube(glm::vec3 position,
         glm::vec3 rotation,
         glm::vec3 scale);

    Cube(glm::vec3 position,
         glm::vec3 rotation,
         glm::vec3 scale,
         Texture* texture);

    Cube(glm::vec3 position,
         glm::vec3 rotation,
         glm::vec3 scale,
         glm::vec3 color);
    ~Cube() override;

    void draw(Shader &shader, glm::mat4 model = glm::mat4(1.0f)) override;

private:
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    Texture* texture = nullptr;
    bool hasColor = false;
    glm::vec3 baseColor{1.0f};
    GLsizei indexCount = 0;

    void init();
};
