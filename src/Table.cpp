#include <Table.h>

#include <Texture.h>
#include <Cube.h>

Table::Table(glm::vec3 position,
             glm::vec3 rotation)
    : Object(position,
             rotation,
             glm::vec3(1.0f)){
    init();
}

void Table::init(){

    Texture* wood = loadTexture("textures/wood_dark.png");

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.67f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.1f, 0.1f, 0.78f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.06f, 0.67, 0.06f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(1.04f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.06f, 0.67, 0.06f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(0.0f, 0.0f, 0.72f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.06f, 0.67, 0.06f),
        wood
    ));

    parts.emplace_back(std::make_unique<Cube>(
        glm::vec3(1.04f, 0.0f, 0.72f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.06f, 0.67, 0.06f),
        wood
    ));
}

void Table::draw(Shader &shader, glm::mat4 model){
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    for (auto &part : parts)
        part->draw(shader, model);
}
