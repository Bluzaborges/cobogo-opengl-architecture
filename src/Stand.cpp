#include <Stand.h>

#include <Texture.h>
#include <Cube.h>

Stand::Stand(glm::vec3 position,
             glm::vec3 rotation)
    : Object(position,
             rotation,
             glm::vec3(1.0f)){
    init();
}

void Stand::init(){

    Texture* light_wood = loadTexture("textures/wood_light.png");
    Texture* dark_wood = loadTexture("textures/wood_dark.png");

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.04f),
        glm::vec3(-90.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 0.04f, 2.20f),
        light_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.525f, 1.805f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.475f, 0.05f, 0.28f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.58f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 0.05f, 0.44f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.02f, 0.63f, 0.04f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(1.55f, 0.02f, 0.44f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.525f, 0.63f, 0.04f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(1.55f, 0.02f, 0.44f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.02f, 1.405f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.485f, 0.02f, 0.44f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.02f, 1.0175f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.485f, 0.02f, 0.44f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 2.18f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.525f, 0.02f, 0.44f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.02f, 0.05f, 0.04f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(0.53f, 0.02f, 0.44f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.75f, 0.05f, 0.04f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(0.53f, 0.02f, 0.44f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(1.4f, 0.05f, 0.04f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(0.53f, 0.02f, 0.44f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(2.0f, 0.05f, 0.04f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(0.53f, 0.02f, 0.44f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.02f, 0.22f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.71f, 0.02f, 0.44f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.02f, 0.39f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.71f, 0.02f, 0.44f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.75f, 0.31f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.63f, 0.02f, 0.44f),
        dark_wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 0.05f, 0.44f),
        dark_wood
    ));
}

void Stand::draw(Shader &shader, glm::mat4 model){
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    for (auto &part : parts)
        part->draw(shader, model);
}
