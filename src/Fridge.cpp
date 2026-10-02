#include <Fridge.h>

#include <Texture.h>
#include <Cube.h>

Fridge::Fridge(glm::vec3 position,
               glm::vec3 rotation)
      : Object(position,
               rotation,
               glm::vec3(1.0f)){
    init();
}

void Fridge::init(){

    Texture* wood = loadTexture("textures/stainless_steel.png");

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.58f, 1.84f, 0.7f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.58f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.09f, 0.80f, 0.7f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.58f, 0.81f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.09f, 1.03f, 0.7f),
        wood
    ));
}

void Fridge::draw(Shader &shader, glm::mat4 model){
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    for (auto &part : parts)
        part->draw(shader, model);
}
