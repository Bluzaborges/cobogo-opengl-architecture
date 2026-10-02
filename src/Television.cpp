#include <Television.h>

#include <Texture.h>
#include <Cube.h>
#include <Cylinder.h>

Television::Television(glm::vec3 position,
                       glm::vec3 rotation)
              : Object(position,
                       rotation,
                       glm::vec3(1.0f)){
    init();
}

void Television::init(){

    Texture* screen = loadTexture("textures/screen.png");
    Texture* frame = loadTexture("textures/wood_white.png");

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.02f, 0.0f, 0.02f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.10f, 0.02f, 0.65f),
        screen
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.14f, 0.03f, 0.02f),
        frame
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.67f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.14f, 0.03f, 0.02f),
        frame
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.02f, 0.0f, 0.02f),
        glm::vec3(0.0f, -90.0f, 0.0f),
        glm::vec3(0.65f, 0.03f, 0.02f),
        frame
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(1.14f, 0.0f, 0.02f),
        glm::vec3(0.0f, -90.0f, 0.0f),
        glm::vec3(0.65f, 0.03f, 0.02f),
        frame
    ));
}

void Television::draw(Shader &shader, glm::mat4 model){
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    for (auto &part : parts)
        part->draw(shader, model);
}
