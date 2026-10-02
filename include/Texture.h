#pragma once

#include <GL/glew.h>
#include <string>

class Texture {
private:
    unsigned int ID = 0;
    int width = 0;
    int height = 0;
    int nrChannels = 0;
    bool ownsTexture = false;

    inline static GLuint missingTextureID = 0;

public:
    explicit Texture(const std::string& path, bool flip = true);
    Texture();
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void bind(unsigned int unit = 0) const;
    static GLuint getMissingTexture();
    static void destroyMissingTexture();
};
