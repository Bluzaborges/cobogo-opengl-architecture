#include "Shader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

Shader::Shader(const char* vertexPath,
               const char* fragmentPath,
               const char* geometryPath) {
    const std::string vertexCode = readFile(vertexPath);
    const std::string fragmentCode = readFile(fragmentPath);
    const std::string geometryCode = geometryPath ? readFile(geometryPath) : std::string{};

    GLuint vertex = 0;
    GLuint fragment = 0;
    GLuint geometry = 0;

    try {
        vertex = compileShader(GL_VERTEX_SHADER, vertexCode, "VERTEX");
        fragment = compileShader(GL_FRAGMENT_SHADER, fragmentCode, "FRAGMENT");

        if (geometryPath)
            geometry = compileShader(GL_GEOMETRY_SHADER, geometryCode, "GEOMETRY");

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);

        if (geometry)
            glAttachShader(ID, geometry);

        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
    }
    catch (...) {
        if (ID)
            glDeleteProgram(ID);
        if (vertex)
            glDeleteShader(vertex);
        if (fragment)
            glDeleteShader(fragment);
        if (geometry)
            glDeleteShader(geometry);
        throw;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometry)
        glDeleteShader(geometry);
}

Shader::~Shader() {
    if (ID)
        glDeleteProgram(ID);
}

Shader::Shader(Shader&& other) noexcept
    : ID(std::exchange(other.ID, 0)) {}

Shader& Shader::operator=(Shader&& other) noexcept {
    if (this == &other)
        return *this;

    if (ID)
        glDeleteProgram(ID);

    ID = std::exchange(other.ID, 0);
    return *this;
}

void Shader::use() const {
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& matrix) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& matrix) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

std::string Shader::readFile(const char* path) {
    std::ifstream file(path);
    if (!file)
        throw std::runtime_error(std::string("Unable to read shader file: ") + path);

    std::ostringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

GLuint Shader::compileShader(GLenum type,
                             const std::string& source,
                             const std::string& label) {
    const char* sourcePointer = source.c_str();
    const GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &sourcePointer, nullptr);
    glCompileShader(shader);

    try {
        checkCompileErrors(shader, label);
    }
    catch (...) {
        glDeleteShader(shader);
        throw;
    }

    return shader;
}

void Shader::checkCompileErrors(GLuint object, const std::string& type) {
    GLint success = GL_FALSE;
    GLchar infoLog[1024]{};

    if (type == "PROGRAM") {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, sizeof(infoLog), nullptr, infoLog);
            throw std::runtime_error("Shader program linking failed:\n" + std::string(infoLog));
        }
        return;
    }

    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(object, sizeof(infoLog), nullptr, infoLog);
        throw std::runtime_error(type + " shader compilation failed:\n" + std::string(infoLog));
    }
}
