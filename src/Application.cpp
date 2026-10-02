#include <Application.h>

#include <iostream>

Application::Application(int width,
                         int height,
                         const std::string& title)
                       : width(width),
                         height(height),
                         title(title),
                         window(nullptr) {}

Application::~Application(){
    if (window)
        glfwDestroyWindow(window);

    glfwTerminate();
}

bool Application::init(){
    if (!glfwInit()) {
        std::cerr << "Error initializing GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window){
        std::cerr << "Error creating window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        std::cerr << "Error initializing GLEW\n";
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    return true;
}

void Application::framebuffer_size_callback(GLFWwindow*, int width, int height){
    glViewport(0, 0, width, height);
}
