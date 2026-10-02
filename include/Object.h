#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

#include <Shader.h>
#include <Texture.h>

class Object {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Object();
    Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    Object(const Object&) = delete;
    Object& operator=(const Object&) = delete;
    Object(Object&&) noexcept = default;
    Object& operator=(Object&&) noexcept = default;

    virtual void draw(Shader& shader, glm::mat4 parentTransform);
    virtual ~Object() = default;

protected:
    Texture* loadTexture(const std::string& path);

private:
    std::vector<std::unique_ptr<Texture>> ownedTextures;
};
