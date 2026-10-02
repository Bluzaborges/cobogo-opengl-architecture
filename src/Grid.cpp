#include "Grid.h"

#include <stdexcept>
#include <vector>

Grid::Grid(int gridSize, int step) {
    if (gridSize <= 0 || step <= 0)
        throw std::invalid_argument("Grid size and step must be positive.");

    std::vector<float> vertices;

    for (int i = -gridSize; i <= gridSize; i += step) {
        vertices.insert(vertices.end(), {
            static_cast<float>(i), 0.0f, static_cast<float>(-gridSize),
            static_cast<float>(i), 0.0f, static_cast<float>(gridSize),
            static_cast<float>(-gridSize), 0.0f, static_cast<float>(i),
            static_cast<float>(gridSize), 0.0f, static_cast<float>(i)
        });
    }

    vertices.insert(vertices.end(), {
        static_cast<float>(-gridSize), 0.0f, 0.0f,
        static_cast<float>(gridSize), 0.0f, 0.0f,
        0.0f, static_cast<float>(-gridSize), 0.0f,
        0.0f, static_cast<float>(gridSize), 0.0f,
        0.0f, 0.0f, static_cast<float>(-gridSize),
        0.0f, 0.0f, static_cast<float>(gridSize)
    });

    vertexCount = static_cast<GLsizei>(vertices.size() / 3);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(vertices.size() * sizeof(float)),
                 vertices.data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

Grid::~Grid() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Grid::draw() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, vertexCount);
    glBindVertexArray(0);
}
