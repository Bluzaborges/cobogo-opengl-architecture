#include <Countertop.h>

#include <Texture.h>
#include <Cube.h>

Countertop::Countertop(glm::vec3 position,
                       glm::vec3 rotation)
              : Object(position,
                       rotation,
                       glm::vec3(1.0f)){
    init();
}

void Countertop::init(){

    Texture* dark_wood = loadTexture("textures/wood_dark.png");
    Texture* light_wood = loadTexture("textures/wood_light.png");

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 1.03f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.18f, 0.05f, 0.67f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.1f, 0.98f, 0.33f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.98f, 0.05f, 0.34f),
        light_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.1f, 0.49f, 0.33f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.98f, 0.05f, 0.34f),
        light_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.1f, 0.0f, 0.33f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.98f, 0.05f, 0.34f),
        light_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.05f, 0.0f, 0.28f),
        glm::vec3(-90.0f, 0.0f, 0.0f),
        glm::vec3(1.08f, 0.05f, 1.03),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.1f, 0.0f, 0.33f),
        glm::vec3(-90.0f, 0.0f, 0.0f),
        glm::vec3(0.98f, 0.05f, 1.03),
        light_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.05f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(1.03f, 0.05f, 0.67f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.1f, 0.0f, 0.28f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(1.03f, 0.05f, 0.39f),
        light_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(1.13f, 0.0f, 0.28f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(1.03f, 0.05f, 0.39f),
        light_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(1.18f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(1.03f, 0.05f, 0.67f),
        dark_wood
    ));
}

void Countertop::draw(Shader &shader, glm::mat4 model){
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    for (auto &part : parts)
        part->draw(shader, model);
}
