#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <exception>
#include <iostream>
#include <stdexcept>

#include "Application.h"
#include "Camera.h"
#include "Grid.h"
#include "SceneBuilder.h"
#include "Shader.h"
#include "Texture.h"

namespace {

bool showGrid = false;
bool wireframeMode = false;
bool showWalls = true;
bool darkBackground = false;
bool gPressed = false;
bool fPressed = false;
bool hPressed = false;
bool bPressed = false;

void processGlobalShortcuts(GLFWwindow* window) {
    auto toggle = [&](int key, bool& pressed, bool& flag) {
        if (glfwGetKey(window, key) == GLFW_PRESS && !pressed) {
            flag = !flag;
            pressed = true;
        }

        if (glfwGetKey(window, key) == GLFW_RELEASE)
            pressed = false;
    };

    toggle(GLFW_KEY_G, gPressed, showGrid);
    toggle(GLFW_KEY_F, fPressed, wireframeMode);
    toggle(GLFW_KEY_H, hPressed, showWalls);
    toggle(GLFW_KEY_B, bPressed, darkBackground);
}

class Framebuffer {
public:
    Framebuffer(int width, int height) {
        glGenFramebuffers(1, &fbo);
        glGenTextures(1, &colorTexture);
        glGenRenderbuffers(1, &depthStencilBuffer);

        try {
            resize(width, height);
        }
        catch (...) {
            glDeleteRenderbuffers(1, &depthStencilBuffer);
            glDeleteTextures(1, &colorTexture);
            glDeleteFramebuffers(1, &fbo);
            throw;
        }
    }

    ~Framebuffer() {
        glDeleteRenderbuffers(1, &depthStencilBuffer);
        glDeleteTextures(1, &colorTexture);
        glDeleteFramebuffers(1, &fbo);
    }

    Framebuffer(const Framebuffer&) = delete;
    Framebuffer& operator=(const Framebuffer&) = delete;

    void resize(int newWidth, int newHeight) {
        if (newWidth <= 0 || newHeight <= 0 ||
            (newWidth == width && newHeight == height))
            return;

        width = newWidth;
        height = newHeight;

        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glBindTexture(GL_TEXTURE_2D, colorTexture);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGB,
                     width,
                     height,
                     0,
                     GL_RGB,
                     GL_UNSIGNED_BYTE,
                     nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D,
                               colorTexture,
                               0);

        glBindRenderbuffer(GL_RENDERBUFFER, depthStencilBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                  GL_DEPTH_STENCIL_ATTACHMENT,
                                  GL_RENDERBUFFER,
                                  depthStencilBuffer);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            throw std::runtime_error("Unable to create the rendering framebuffer.");
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    }

    GLuint texture() const {
        return colorTexture;
    }

private:
    GLuint fbo = 0;
    GLuint colorTexture = 0;
    GLuint depthStencilBuffer = 0;
    int width = 0;
    int height = 0;
};

class FullscreenQuad {
public:
    FullscreenQuad() {
        constexpr float vertices[] = {
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
             1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f, 1.0f
        };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              4 * sizeof(float),
                              reinterpret_cast<void*>(2 * sizeof(float)));

        glBindVertexArray(0);
    }

    ~FullscreenQuad() {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    FullscreenQuad(const FullscreenQuad&) = delete;
    FullscreenQuad& operator=(const FullscreenQuad&) = delete;

    void draw() const {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

private:
    GLuint vao = 0;
    GLuint vbo = 0;
};

}

int main() {
    Application app(1024, 768, "Cobogo OpenGL Architecture");
    if (!app.init())
        return -1;

    try {
        {
            glfwSetInputMode(app.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(app.getWindow(), mouse_callback);

            Shader objectShader("shaders/object.vertex.glsl", "shaders/object.fragment.glsl");
            Shader gridShader("shaders/grid.vertex.glsl", "shaders/grid.fragment.glsl");
            Shader skyShader("shaders/sky.vertex.glsl", "shaders/sky.fragment.glsl");
            Shader vignetteShader("shaders/vignette.vertex.glsl", "shaders/vignette.fragment.glsl");

            vignetteShader.use();
            vignetteShader.setInt("screenTexture", 0);

            auto floors = buildFloor();
            auto walls = buildWalls();
            auto objects = buildObjects();
            Grid grid;

            int framebufferWidth = 0;
            int framebufferHeight = 0;
            glfwGetFramebufferSize(app.getWindow(), &framebufferWidth, &framebufferHeight);

            Framebuffer framebuffer(framebufferWidth, framebufferHeight);
            FullscreenQuad fullscreenQuad;

            glEnable(GL_DEPTH_TEST);

            while (!glfwWindowShouldClose(app.getWindow())) {
                glfwGetFramebufferSize(app.getWindow(), &framebufferWidth, &framebufferHeight);
                if (framebufferWidth <= 0 || framebufferHeight <= 0) {
                    glfwWaitEvents();
                    continue;
                }

                framebuffer.resize(framebufferWidth, framebufferHeight);
                glViewport(0, 0, framebufferWidth, framebufferHeight);

                updateDeltaTime();
                processInput(app.getWindow());
                processGlobalShortcuts(app.getWindow());

                framebuffer.bind();
                glEnable(GL_DEPTH_TEST);

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glDepthMask(GL_FALSE);

                skyShader.use();
                skyShader.setBool("darkMode", darkBackground);
                fullscreenQuad.draw();
                glDepthMask(GL_TRUE);

                if (wireframeMode) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    glEnable(GL_POLYGON_OFFSET_LINE);
                }
                else {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }

                const float aspectRatio = static_cast<float>(framebufferWidth) /
                                          static_cast<float>(framebufferHeight);
                glm::mat4 projection = glm::perspective(glm::radians(60.0f),
                                                        aspectRatio,
                                                        0.5f,
                                                        100.0f);
                glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
                glm::mat4 model(1.0f);

                objectShader.use();
                objectShader.setMat4("projection", projection);
                objectShader.setMat4("view", view);
                objectShader.setVec3("lightDir", glm::normalize(glm::vec3(0.4f, 1.0f, 0.3f)));

                if (!wireframeMode) {
                    for (auto& floor : floors)
                        floor.draw(objectShader, model);
                }

                if (showWalls) {
                    for (auto& wall : walls)
                        wall.draw(objectShader, model);
                }

                for (auto& object : objects)
                    object->draw(objectShader, model);

                if (showGrid) {
                    gridShader.use();
                    gridShader.setMat4("projection", projection);
                    gridShader.setMat4("view", view);
                    gridShader.setMat4("model", glm::mat4(1.0f));
                    gridShader.setVec3("gridColor", glm::vec3(0.9f));
                    grid.draw();
                }

                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                glDisable(GL_DEPTH_TEST);
                glClear(GL_COLOR_BUFFER_BIT);

                vignetteShader.use();
                glBindTexture(GL_TEXTURE_2D, framebuffer.texture());
                fullscreenQuad.draw();

                glfwSwapBuffers(app.getWindow());
                glfwPollEvents();
            }
        }

        Texture::destroyMissingTexture();
    }
    catch (const std::exception& error) {
        Texture::destroyMissingTexture();
        std::cerr << "Error: " << error.what() << '\n';
        return -1;
    }

    return 0;
}
