#include <Chair.h>

#include <Texture.h>
#include <Cube.h>

Chair::Chair(glm::vec3 position,
             glm::vec3 rotation)
    : Object(position,
             rotation,
             glm::vec3(1.0f)){
    init();
}

void Chair::init(){

    Texture* wood = loadTexture("textures/wood_dark.png");
    Texture* upholstery = loadTexture("textures/upholstery_light.png");

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.06f, 0.38f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.42f, 0.10f, 0.42f),
        upholstery
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.06f, 0.38f, 0.0f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(0.58f, 0.06f, 0.42f),
        upholstery
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.05f, 0.38f, 0.03f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.43f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.05f, 0.38f, 0.03f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.39f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.05f, 0.38f, 0.03f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.43f, 0.0f, 0.39f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.05f, 0.38f, 0.03f),
        wood
    ));
}

void Chair::draw(Shader &shader, glm::mat4 model){
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    for (auto &part : parts)
        part->draw(shader, model);
}
