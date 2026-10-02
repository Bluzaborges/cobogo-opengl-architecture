#pragma once

#include <GL/glew.h>

class Grid {
public:
    explicit Grid(int gridSize = 20, int step = 1);
    ~Grid();

    Grid(const Grid&) = delete;
    Grid& operator=(const Grid&) = delete;

    void draw() const;

private:
    GLuint vao = 0;
    GLuint vbo = 0;
    GLsizei vertexCount = 0;
};
