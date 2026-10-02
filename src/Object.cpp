#include <Object.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Object::Object()
    : position(0.0f),
      rotation(0.0f),
      scale(1.0f) {}

Object::Object(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : position(position),
      rotation(rotation),
      scale(scale) {}

Texture* Object::loadTexture(const std::string& path)
{
    auto texture = std::make_unique<Texture>(path);
    Texture* result = texture.get();
    ownedTextures.push_back(std::move(texture));
    return result;
}

void Object::draw(Shader& shader, glm::mat4 parentTransform)
{
    glm::mat4 model = parentTransform;

    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, scale);

    shader.setMat4("model", model);
}
