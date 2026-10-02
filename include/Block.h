#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>

#include <Object.h>
#include <Shader.h>
#include <Texture.h>

class Block : public Object {
public:
    Block(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    Block(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color);
    Block(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Texture* texture);
    Block(glm::vec3 position,
          glm::vec3 rotation,
          glm::vec3 scale,
          std::shared_ptr<Texture> texture);

    void draw(Shader& shader, glm::mat4 model) override;

private:
    void init();
    std::shared_ptr<Texture> textureOwner;
    Texture* texture = nullptr;
    std::vector<std::unique_ptr<Object>> parts;

    glm::vec3 baseColor = glm::vec3(0.972f, 0.972f, 1.0f);
};
