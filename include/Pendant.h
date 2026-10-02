#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>

#include <Object.h>
#include <Shader.h>

class Pendant : public Object {
public:
    Pendant(glm::vec3 position, glm::vec3 rotation);

    void init();
    void draw(Shader &shader, glm::mat4 model) override;

private:
    std::vector<std::unique_ptr<Object>> parts;
};
