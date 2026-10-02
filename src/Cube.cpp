#include "Cube.h"

namespace {

constexpr float cubeVertices[] = {
    // positions      // normals         // texture
    // back face
    0.0f,0.0f,0.0f,   0.0f,0.0f,-1.0f,   0.0f,1.0f,
    1.0f,0.0f,0.0f,   0.0f,0.0f,-1.0f,   1.0f,1.0f,
    1.0f,1.0f,0.0f,   0.0f,0.0f,-1.0f,   1.0f,0.0f,
    0.0f,1.0f,0.0f,   0.0f,0.0f,-1.0f,   0.0f,0.0f,

    // front face
    0.0f,0.0f,1.0f,   0.0f,0.0f,1.0f,    0.0f,0.0f,
    1.0f,0.0f,1.0f,   0.0f,0.0f,1.0f,    1.0f,0.0f,
    1.0f,1.0f,1.0f,   0.0f,0.0f,1.0f,    1.0f,1.0f,
    0.0f,1.0f,1.0f,   0.0f,0.0f,1.0f,    0.0f,1.0f,

    // left face
    0.0f,0.0f,0.0f,  -1.0f,0.0f,0.0f,    1.0f,1.0f,
    0.0f,1.0f,0.0f,  -1.0f,0.0f,0.0f,    1.0f,0.0f,
    0.0f,1.0f,1.0f,  -1.0f,0.0f,0.0f,    0.0f,0.0f,
    0.0f,0.0f,1.0f,  -1.0f,0.0f,0.0f,    0.0f,1.0f,

    // right face
    1.0f,0.0f,0.0f,   1.0f,0.0f,0.0f,    0.0f,1.0f,
    1.0f,1.0f,0.0f,   1.0f,0.0f,0.0f,    0.0f,0.0f,
    1.0f,1.0f,1.0f,   1.0f,0.0f,0.0f,    1.0f,0.0f,
    1.0f,0.0f,1.0f,   1.0f,0.0f,0.0f,    1.0f,1.0f,

    // top face
    0.0f,1.0f,0.0f,   0.0f,1.0f,0.0f,    0.0f,1.0f,
    1.0f,1.0f,0.0f,   0.0f,1.0f,0.0f,    1.0f,1.0f,
    1.0f,1.0f,1.0f,   0.0f,1.0f,0.0f,    1.0f,0.0f,
    0.0f,1.0f,1.0f,   0.0f,1.0f,0.0f,    0.0f,0.0f,

    // bottom face
    0.0f,0.0f,0.0f,   0.0f,-1.0f,0.0f,   0.0f,0.0f,
    1.0f,0.0f,0.0f,   0.0f,-1.0f,0.0f,   1.0f,0.0f,
    1.0f,0.0f,1.0f,   0.0f,-1.0f,0.0f,   1.0f,1.0f,
    0.0f,0.0f,1.0f,   0.0f,-1.0f,0.0f,   0.0f,1.0f
};

constexpr unsigned int cubeIndices[] = {
    0,1,2,    2,3,0,
    4,5,6,    6,7,4,
    8,9,10,   10,11,8,
    12,13,14, 14,15,12,
    16,17,18, 18,19,16,
    20,21,22, 22,23,20
};

}

Cube::Cube(glm::vec3 position,
           glm::vec3 rotation,
           glm::vec3 scale)
    : Object(position, rotation, scale) {
    init();
}

Cube::~Cube() {
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

Cube::Cube(glm::vec3 position,
           glm::vec3 rotation,
           glm::vec3 scale,
           Texture* texture)
    : Object(position, rotation, scale), texture(texture) {
    init();
}

Cube::Cube(glm::vec3 position,
           glm::vec3 rotation,
           glm::vec3 scale,
           glm::vec3 color)
    : Object(position, rotation, scale), hasColor(true), baseColor(color) {
    init();
}

void Cube::init(){
    indexCount = sizeof(cubeIndices) / sizeof(unsigned int);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

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

void Cube::draw(Shader &shader, glm::mat4 model) {

    model = glm::translate(model, position);
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
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else {
        shader.setBool("useTexture", true);
        shader.setBool("useColor", false);
        glBindTexture(GL_TEXTURE_2D, Texture::getMissingTexture());
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
