#include <Desk.h>

#include <Texture.h>
#include <Cube.h>

Desk::Desk(glm::vec3 position,
           glm::vec3 rotation)
  : Object(position,
           rotation,
           glm::vec3(1.0f)){
    init();
}

void Desk::init(){

    Texture* wood = loadTexture("textures/wood_light.png");

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.55f, 0.72f, 0.0f),
        glm::vec3(0.0f, -90.0f, 0.0f),
        glm::vec3(1.20f, 0.04f, 0.55f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.37f, 0.0f),
        glm::vec3(-90.0f, 0.0f, -90.0f),
        glm::vec3(1.16f, 0.04f, 0.35f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.72f, 1.20f),
        glm::vec3(0.0f, 90.0f, -90.0f),
        glm::vec3(0.72f, 0.04f, 0.55f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 0.72f, 0.08f),
        glm::vec3(0.0f, 90.0f, -90.0f),
        glm::vec3(0.72f, 0.04f, 0.15f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 0.37f, 0.04f),
        glm::vec3(-90.0f, 90.0f, -90.0f),
        glm::vec3(1.62f, 0.04f, 0.35f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.55f, 0.72f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.15f, 0.04f, 0.55f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(1.66f, 0.72f, 0.0f),
        glm::vec3(0.0f, 0.0f, -90.0f),
        glm::vec3(0.72f, 0.04f, 0.55f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 0.72f, 0.04f),
        glm::vec3(0.0f, 0.0f, -90.0f),
        glm::vec3(0.72f, 0.04f, 0.15f),
        wood
    ));
}

void Desk::draw(Shader &shader, glm::mat4 model){
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    for (auto &part : parts)
        part->draw(shader, model);
}
