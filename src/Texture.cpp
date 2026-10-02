#include <Texture.h>

#include <stb_image.h>
#include <iostream>
#include <utility>

Texture::Texture(const std::string& path, bool flip) {
    stbi_set_flip_vertically_on_load(flip);

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << path << '\n';
        ID = getMissingTexture();
        return;
    }

    glGenTextures(1, &ID);
    ownsTexture = true;
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = GL_RGB;
    if (nrChannels == 1)
        format = GL_RED;
    else if (nrChannels == 2)
        format = GL_RG;
    else if (nrChannels == 4)
        format = GL_RGBA;

    GLint previousAlignment = 0;
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &previousAlignment);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, previousAlignment);

    stbi_image_free(data);
}

Texture::Texture() {
    ID = getMissingTexture();
}

Texture::~Texture() {
    if (ownsTexture && ID != 0)
        glDeleteTextures(1, &ID);
}

Texture::Texture(Texture&& other) noexcept
    : ID(std::exchange(other.ID, 0)),
      width(std::exchange(other.width, 0)),
      height(std::exchange(other.height, 0)),
      nrChannels(std::exchange(other.nrChannels, 0)),
      ownsTexture(std::exchange(other.ownsTexture, false)) {}

Texture& Texture::operator=(Texture&& other) noexcept {
    if (this == &other)
        return *this;

    if (ownsTexture && ID != 0)
        glDeleteTextures(1, &ID);

    ID = std::exchange(other.ID, 0);
    width = std::exchange(other.width, 0);
    height = std::exchange(other.height, 0);
    nrChannels = std::exchange(other.nrChannels, 0);
    ownsTexture = std::exchange(other.ownsTexture, false);
    return *this;
}

void Texture::bind(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

GLuint Texture::getMissingTexture() {
    if (missingTextureID == 0) {
        const int size = 2;
        unsigned char data[size * size * 3] = {
            255, 0, 255,   0,   0, 0,
            0,   0, 0,     255, 0, 255
        };

        GLint previousAlignment = 0;
        glGetIntegerv(GL_UNPACK_ALIGNMENT, &previousAlignment);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1, &missingTextureID);
        glBindTexture(GL_TEXTURE_2D, missingTextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glPixelStorei(GL_UNPACK_ALIGNMENT, previousAlignment);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    return missingTextureID;
}

void Texture::destroyMissingTexture() {
    if (missingTextureID == 0)
        return;

    glDeleteTextures(1, &missingTextureID);
    missingTextureID = 0;
}
