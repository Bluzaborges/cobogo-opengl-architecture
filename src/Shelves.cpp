#include <Shelves.h>

#include <Texture.h>
#include <Cube.h>

Shelves::Shelves(glm::vec3 position,
                 glm::vec3 rotation)
        : Object(position,
                 rotation,
                 glm::vec3(1.0f)){
    init();
}

void Shelves::init(){

    Texture* wood = loadTexture("textures/wood_white.png");

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 0.0f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.16f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.45f, 0.15f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.75f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.45f, 0.30f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.75f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.45f, 0.45f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.75f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.45f, 0.60f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.75f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.45f, 1.80f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.75f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 2.25f, 0.04f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.16f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 0.0f, 2.25f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.16f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.45f, 0.45f, 2.25f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.75f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.45f, 0.90f, 2.25f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.75f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.45f, 1.35f, 2.25f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.75f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.45f, 1.80f, 2.25f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.75f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 2.25f, 2.25f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.16f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 0.0f, 2.25f),
        glm::vec3(0.0f, 90.0f, 0.0f),
        glm::vec3(1.80f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 0.45f, 2.25f),
        glm::vec3(0.0f, 90.0f, 0.0f),
        glm::vec3(1.80f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 0.90f, 2.25f),
        glm::vec3(0.0f, 90.0f, 0.0f),
        glm::vec3(1.80f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 1.35f, 2.25f),
        glm::vec3(0.0f, 90.0f, 0.0f),
        glm::vec3(1.80f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 1.80f, 2.25f),
        glm::vec3(0.0f, 90.0f, 0.0f),
        glm::vec3(1.80f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 2.25f, 2.25f),
        glm::vec3(0.0f, 90.0f, 0.0f),
        glm::vec3(1.80f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 0.0f, 0.04f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(2.29f, 0.04f, 2.62f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 90.0f, 90.0f),
        glm::vec3(2.29f, 0.04f, 1.2f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 2.66f),
        glm::vec3(0.0f, 90.0f, 90.0f),
        glm::vec3(2.29f, 0.04f, 1.2f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.45f, 0.04f, 0.04f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(2.21f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.45f, 0.04f, 2.25f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(2.21f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 0.04f, 2.25f),
        glm::vec3(0.0f, 90.0f, 90.0f),
        glm::vec3(2.21f, 0.04f, 0.41f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.04f, 0.04f, 0.41f),
        glm::vec3(0.0f, 90.0f, 90.0f),
        glm::vec3(2.21f, 0.04f, 0.41f),
        wood
    ));
}

void Shelves::draw(Shader &shader, glm::mat4 model){
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    for (auto &part : parts)
        part->draw(shader, model);
}
