#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Application {
public:
    Application(int width, int height, const std::string& title);
    ~Application();

    bool init();

    GLFWwindow* getWindow() const { return window; }

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:
    int width;
    int height;
    std::string title;
    GLFWwindow* window;
};
