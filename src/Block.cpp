#include <Block.h>

#include <Cube.h>

Block::Block(glm::vec3 position,
             glm::vec3 rotation,
             glm::vec3 scale)
           : Object(position, rotation, scale){
    init();
}

Block::Block(glm::vec3 position,
             glm::vec3 rotation,
             glm::vec3 scale,
             glm::vec3 color)
           : Object(position, rotation, scale),
             baseColor(color){
    init();
}

Block::Block(glm::vec3 position,
             glm::vec3 rotation,
             glm::vec3 scale,
             Texture* texture)
           : Object(position, rotation, scale),
             texture(texture){
    init();
}

Block::Block(glm::vec3 position,
             glm::vec3 rotation,
             glm::vec3 scale,
             std::shared_ptr<Texture> texture)
           : Object(position, rotation, scale),
             textureOwner(std::move(texture)),
             texture(textureOwner.get()){
    init();
}

void Block::init() {
    if (texture) {
        parts.emplace_back(std::make_unique<Cube>(
            glm::vec3(0.0f),
            glm::vec3(0.0f),
            glm::vec3(1.0f),
            texture
        ));
    } else {
        parts.emplace_back(std::make_unique<Cube>(
            glm::vec3(0.0f),
            glm::vec3(0.0f),
            glm::vec3(1.0f),
            baseColor
        ));
    }
}

void Block::draw(Shader& shader, glm::mat4 model) {
    model = glm::translate(model, position);

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, scale);

    shader.setVec2("uvScale", glm::vec2(scale.x, scale.z));

    for (auto& part : parts)
        part->draw(shader, model);

    shader.setVec2("uvScale", glm::vec2(1.0f, 1.0f));
}
