#include "Cylinder.h"

#include <glm/gtc/constants.hpp>
#include <cmath>
#include <stdexcept>

Cylinder::Cylinder(glm::vec3 position,
                   glm::vec3 rotation,
                   glm::vec3 scale,
                   int segments)
    : Object(position, rotation, scale){
    init(segments);
}

Cylinder::~Cylinder() {
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

Cylinder::Cylinder(glm::vec3 position,
                   glm::vec3 rotation,
                   glm::vec3 scale,
                   Texture* texture,
                   int segments)
    : Object(position, rotation, scale), texture(texture){
    init(segments);
}

Cylinder::Cylinder(glm::vec3 position,
                   glm::vec3 rotation,
                   glm::vec3 scale,
                   glm::vec3 color,
                   int segments)
    : Object(position, rotation, scale), hasColor(true), baseColor(color){
    init(segments);
}

void Cylinder::init(int segments) {
    if (segments < 3)
        throw std::invalid_argument("A cylinder requires at least three segments.");

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    float radius = 0.5f;
    float height = 1.0f;

    // side vertices (positions, normals, texture)
    for (int i = 0; i <= segments; i++) {
        float theta = static_cast<float>(i) / segments * 2.0f * glm::pi<float>();
        float x = std::cos(theta);
        float z = std::sin(theta);
        float u = static_cast<float>(i) / segments;

        // top ring
        vertices.insert(vertices.end(), {radius * x, height / 2, radius * z,  x, 0, z,  u, 0.0f});

        // bottom ring
        vertices.insert(vertices.end(), {radius * x, -height / 2, radius * z,  x, 0, z,  u, 1.0f});
    }

    // side indices
    for (int i = 0; i < segments; i++) {
        unsigned int top1 = static_cast<unsigned int>(i * 2);
        unsigned int bot1 = static_cast<unsigned int>(i * 2 + 1);
        unsigned int top2 = static_cast<unsigned int>((i + 1) * 2);
        unsigned int bot2 = static_cast<unsigned int>((i + 1) * 2 + 1);

        indices.insert(indices.end(), {top1, bot1, top2});
        indices.insert(indices.end(), {top2, bot1, bot2});
    }

    // top and bottom centers
    unsigned int baseIndex = static_cast<unsigned int>((segments + 1) * 2);
    vertices.insert(vertices.end(), {0, height / 2, 0,  0, 1, 0,  0.5f, 0.5f});   // top center
    vertices.insert(vertices.end(), {0, -height / 2, 0,  0, -1, 0,  0.5f, 0.5f}); // bottom center

    unsigned int topCenter = baseIndex;
    unsigned int bottomCenter = baseIndex + 1;

    // top and bottom triangles
    for (int i = 0; i < segments; i++) {
        unsigned int topOuter1 = static_cast<unsigned int>(i * 2);
        unsigned int topOuter2 = static_cast<unsigned int>(((i + 1) % (segments + 1)) * 2);
        unsigned int botOuter1 = static_cast<unsigned int>(i * 2 + 1);
        unsigned int botOuter2 = static_cast<unsigned int>(((i + 1) % (segments + 1)) * 2 + 1);

        indices.insert(indices.end(), {topCenter, topOuter2, topOuter1});
        indices.insert(indices.end(), {bottomCenter, botOuter1, botOuter2});
    }

    // store index count
    indexCount = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Cylinder::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
    model = glm::translate(model, glm::vec3(0.0f, scale.y / 2.0f, 0.0f));

    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0,1,0));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1,0,0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0,0,1));

    model = glm::scale(model, scale);

    shader.setMat4("model", model);

    if (texture) {
        shader.setBool("useTexture", true);
        shader.setBool("useColor", false);
        texture->bind(0);
        shader.setInt("texture1", 0);
    }
    else if (hasColor) {
        shader.setBool("useTexture", false);
        shader.setBool("useColor", true);
        shader.setVec3("baseColor", baseColor);
    }
    else {
        shader.setBool("useTexture", false);
        shader.setBool("useColor", true);
        shader.setVec3("baseColor", glm::vec3(0.8f, 0.8f, 0.8f));
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
