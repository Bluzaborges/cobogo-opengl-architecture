#include <Pendant.h>

#include <Texture.h>
#include <Cylinder.h>

Pendant::Pendant(glm::vec3 position,
                 glm::vec3 rotation)
        : Object(position,
                 rotation,
                 glm::vec3(1.0f)){
    init();
}

void Pendant::init(){

    Texture* wood = loadTexture("textures/wood_dark.png");
    Texture* matte = loadTexture("textures/matte_white.png");

    parts.emplace_back(std::make_unique<Cylinder>(
        glm::vec3(0.025f, 0.0f, 0.025f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.005f, 0.5f, 0.005f),
        wood,
        48
    ));

    parts.emplace_back(std::make_unique<Cylinder>(
        glm::vec3(0.025f, 0.0f, 0.025f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        matte,
        48
    ));
}

void Pendant::draw(Shader &shader, glm::mat4 model){
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    for (auto &part : parts)
        part->draw(shader, model);
}
