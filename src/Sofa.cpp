#include <Sofa.h>

#include <Texture.h>
#include <Cube.h>

Sofa::Sofa(glm::vec3 position,
           glm::vec3 rotation)
  : Object(position,
           rotation,
           glm::vec3(1.0f)){
    init();
}

void Sofa::init(){

    Texture* upholstery = loadTexture("textures/upholstery_dark.png");

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.86f, 0.6f, 0.26f),
        upholstery
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 1.84f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.86f, 0.6f, 0.26f),
        upholstery
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.20f, 0.0f, 0.26f),
        glm::vec3(0.0f, -90.0f, 0.0f),
        glm::vec3(1.58f, 0.6f, 0.20f),
        upholstery
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.20f, 0.0f, 0.26f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.79f, 0.45f, 0.78f),
        upholstery
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.20f, 0.0f, 1.06f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.79f, 0.45f, 0.78f),
        upholstery
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.40f, 0.45f, 0.26f),
        glm::vec3(0.0f, -90.0f, 0.0f),
        glm::vec3(0.78f, 0.6f, 0.20f),
        upholstery
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.40f, 0.45f, 1.06f),
        glm::vec3(0.0f, -90.0f, 0.0f),
        glm::vec3(0.78f, 0.6f, 0.20f),
        upholstery
    ));
}

void Sofa::draw(Shader &shader, glm::mat4 model){
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    for (auto &part : parts)
        part->draw(shader, model);
}
