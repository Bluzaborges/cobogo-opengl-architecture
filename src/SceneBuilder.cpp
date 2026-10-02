#include <SceneBuilder.h>

#include <glm/glm.hpp>

#include <Block.h>
#include <Desk.h>
#include <Fridge.h>
#include <Countertop.h>
#include <Table.h>
#include <Chair.h>
#include <Shelves.h>
#include <Stand.h>
#include <Sofa.h>
#include <Television.h>
#include <Pendant.h>

std::vector<Block> buildFloor() {

    std::vector<Block> f;

    auto dark_laminate = std::make_shared<Texture>("textures/laminate_dark.png");
    auto porcelain = std::make_shared<Texture>("textures/porcelain.png");

    f.emplace_back(glm::vec3(1.15f, -0.01f, 1.15f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.01f, 3.65f), dark_laminate);
    f.emplace_back(glm::vec3(3.15f, -0.01f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.25f, 0.01f, 0.8f), dark_laminate);
    f.emplace_back(glm::vec3(6.0f, -0.01f, 1.15f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.4f, 0.01f, 2.85f), dark_laminate);
    f.emplace_back(glm::vec3(4.65f, -0.01f, 1.15f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.20f, 0.01f, 2.7f), dark_laminate);
    f.emplace_back(glm::vec3(2.0f, -0.01f, 4.95f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.125f, 0.01f, 2.75f), dark_laminate);
    f.emplace_back(glm::vec3(2.0f, -0.01f, 7.7f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.01f, 1.8f), dark_laminate);

    f.emplace_back(glm::vec3(3.15f, -0.01f, 7.85f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.925f, 0.01f, 1.65f), porcelain);
    f.emplace_back(glm::vec3(7.275f, -0.01f, 4.95f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.125f, 0.01f, 2.75f), porcelain);
    f.emplace_back(glm::vec3(3.30f, -0.01f, 1.15f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.20f, 0.01f, 2.7f), porcelain);
    f.emplace_back(glm::vec3(7.275f, -0.01f, 7.7f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.8f, 0.01f, 0.15f), porcelain);
    f.emplace_back(glm::vec3(3.0f, -0.01f, 7.7f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.125f, 0.01f, 0.15f), dark_laminate);
    f.emplace_back(glm::vec3(3.0f, -0.01f, 7.85f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.15f, 0.01f, 0.8f), dark_laminate);
    f.emplace_back(glm::vec3(7.125f, -0.01f, 5.525f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.075f, 0.01f, 1.6f), dark_laminate);
    f.emplace_back(glm::vec3(7.2f, -0.01f, 5.525f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.075f, 0.01f, 1.6f), porcelain);
    f.emplace_back(glm::vec3(5.85f, -0.01f, 1.7f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.15f, 0.01f, 1.6f), dark_laminate);
    f.emplace_back(glm::vec3(1.925f, -0.01f, 8.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.075f, 0.01f, 0.8f), dark_laminate);
    f.emplace_back(glm::vec3(3.5f, -0.01f, 4.8f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.8f, 0.01f, 0.15f), dark_laminate);
    f.emplace_back(glm::vec3(3.5f, -0.01f, 3.85f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.8f, 0.01f, 0.075f), porcelain);
    f.emplace_back(glm::vec3(3.5f, -0.01f, 3.925f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.8f, 0.01f, 0.075f), dark_laminate);

    return f;
}

std::vector<Block> buildWalls() {

    std::vector<Block> w;

    w.emplace_back(glm::vec3(1.15f, 0.0f, 1.0f),     glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.15f, 2.45f, 0.15f));
    w.emplace_back(glm::vec3(8.55f, 0.0f, 1.0f),     glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.15f, 2.45f, 0.15f));

    w.emplace_back(glm::vec3(1.15f, 2.05f, 2.15f),   glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.20f, 0.40f, 0.15f));
    w.emplace_back(glm::vec3(8.55f, 2.05f, 2.15f),   glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.20f, 0.40f, 0.15f));

    w.emplace_back(glm::vec3(1.15f, 0.0f, 2.15f),    glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.20f, 1.0f, 0.15f));
    w.emplace_back(glm::vec3(8.55f, 0.0f, 2.15f),    glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.20f, 1.0f, 0.15f));

    w.emplace_back(glm::vec3(1.15f, 0.0f, 3.35f),    glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.60f, 2.45f, 0.15f));
    w.emplace_back(glm::vec3(8.55f, 0.0f, 3.35f),    glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.60f, 2.45f, 0.15f));

    w.emplace_back(glm::vec3(1.0f, 0.0f, 1.0f),      glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(2.6f, 2.45f, 0.15f));

    w.emplace_back(glm::vec3(3.6f, 0.0f, 1.0f),      glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(0.6f, 1.45f, 0.15f));
    w.emplace_back(glm::vec3(3.6f, 2.05f, 1.0f),     glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(0.6f, 0.40f, 0.15f));

    w.emplace_back(glm::vec3(3.30f, 0.0f, 1.0f),     glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(3.0f, 2.45f, 0.15f));
    w.emplace_back(glm::vec3(4.65f, 0.0f, 1.0f),     glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(3.0f, 2.45f, 0.15f));

    w.emplace_back(glm::vec3(6.0f, 0.0f, 1.0f),      glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(0.7f, 2.45f, 0.15f));
    w.emplace_back(glm::vec3(6.0f, 0.0f, 3.3f),      glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(0.7f, 2.45f, 0.15f));

    w.emplace_back(glm::vec3(6.0f, 2.05f, 1.7f),     glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.6f, 0.40f, 0.15f));
    w.emplace_back(glm::vec3(7.275f, 2.05f, 5.525f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.6f, 0.40f, 0.15f));

    w.emplace_back(glm::vec3(3.30f, 2.05f, 4.0f),    glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(0.80f, 0.40f, 0.15f));
    w.emplace_back(glm::vec3(4.65f, 2.05f, 4.0f),    glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(0.80f, 0.40f, 0.15f));
    w.emplace_back(glm::vec3(2.0f, 2.05f, 8.50f),    glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(0.80f, 0.40f, 0.15f));
    w.emplace_back(glm::vec3(7.275f, 2.05f, 7.7f),   glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(0.80f, 0.40f, 0.15f));
    w.emplace_back(glm::vec3(3.5f, 2.05f, 4.8f),     glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(0.80f, 0.40f, 0.15f));
    w.emplace_back(glm::vec3(3.5f, 2.05f, 3.85f),    glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(0.80f, 0.40f, 0.15f));
    w.emplace_back(glm::vec3(3.15f, 2.05f, 7.85f),   glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(0.80f, 0.40f, 0.15f));

    w.emplace_back(glm::vec3(3.15f, 0.0f, 3.85f),    glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(0.35f, 2.45f, 0.15f));
    w.emplace_back(glm::vec3(2.0f, 0.0f, 9.3f),      glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(0.35f, 2.45f, 0.15f));

    w.emplace_back(glm::vec3(4.2f, 0.0f, 1.0f),      glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(4.35f, 2.45f, 0.15f));
    w.emplace_back(glm::vec3(4.30f, 0.0f, 4.8f),     glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(4.25f, 2.45f, 0.15f));
    w.emplace_back(glm::vec3(4.30f, 0.0f, 3.85f),    glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(1.7f,  2.45f, 0.15f));

    w.emplace_back(glm::vec3(7.275f, 0.0f, 4.8f),    glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(0.725f, 2.45f, 0.15f));
    w.emplace_back(glm::vec3(7.275f, 0.0f, 7.125f),  glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(0.725f, 2.45f, 0.15f));

    w.emplace_back(glm::vec3(1.0f, 0.0f, 4.8f),      glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(2.50f, 2.45f, 0.15f));
    w.emplace_back(glm::vec3(5.125f, 0.0f, 7.7f),    glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(2.15f, 2.45f, 0.15f));
    w.emplace_back(glm::vec3(8.225f, 0.0f, 7.7f),    glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.95f, 2.45f, 0.15f));
    w.emplace_back(glm::vec3(1.85f, 0.0f, 9.5f),     glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(6.375f, 2.45f, 0.15f));
    w.emplace_back(glm::vec3(3.15f, 0.0f, 8.65f),    glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(1.0f, 2.45f, 0.15f));
    w.emplace_back(glm::vec3(2.0f, 0.0f, 4.8f),      glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(3.70f, 2.45f, 0.15f));

    w.emplace_back(glm::vec3(2.0f, 2.05f, 7.7f),     glm::vec3(0.0f,  0.0f, 0.0f),  glm::vec3(3.325f, 0.40f, 0.15f));

    return w;
}

std::vector<std::unique_ptr<Object>> buildObjects() {
    std::vector<std::unique_ptr<Object>> objects;

    objects.push_back(std::make_unique<Desk>(glm::vec3(1.15f, 0.0f, 4.80f), glm::vec3(0.0f, 90.0f, 0.0f)));
    objects.push_back(std::make_unique<Fridge>(glm::vec3(3.15f, 0.0f, 9.5f), glm::vec3(0.0f, 90.0f, 0.0f)));
    objects.push_back(std::make_unique<Countertop>(glm::vec3(3.945f, 0.0f, 7.18f), glm::vec3(0.0f, 0.0f, 0.0f)));
    objects.push_back(std::make_unique<Table>(glm::vec3(2.58f, 0.0f, 6.6f), glm::vec3(0.0f, 90.0f, 0.0f)));

    objects.push_back(std::make_unique<Chair>(glm::vec3(2.35f, 0.0f, 6.05f), glm::vec3(0.0f, 0.0f, 0.0f)));
    objects.push_back(std::make_unique<Chair>(glm::vec3(2.35f, 0.0f, 5.6f), glm::vec3(0.0f, 0.0f, 0.0f)));
    objects.push_back(std::make_unique<Chair>(glm::vec3(3.6f, 0.0f, 6.475f), glm::vec3(0.0f, 180.0f, 0.0f)));
    objects.push_back(std::make_unique<Chair>(glm::vec3(3.6f, 0.0f, 6.025f), glm::vec3(0.0f, 180.0f, 0.0f)));

    objects.push_back(std::make_unique<Shelves>(glm::vec3(4.65f, 0.0f, 1.15f), glm::vec3(0.0f, 0.0f, 0.0f)));
    objects.push_back(std::make_unique<Stand>(glm::vec3(7.125f, 0.0f, 7.7f), glm::vec3(0.0f, 180.0f, 0.0f)));
    objects.push_back(std::make_unique<Sofa>(glm::vec3(7.025f, 0.0f, 4.97f), glm::vec3(0.0f, -90.0f, 0.0f)));
    objects.push_back(std::make_unique<Television>(glm::vec3(5.3f, 0.9f, 7.66f), glm::vec3(-90.0f, 0.0f, 0.0f)));

    objects.push_back(std::make_unique<Pendant>(glm::vec3(4.2f, 1.95f, 7.5f), glm::vec3(0.0f, 0.0f, 0.0f)));
    objects.push_back(std::make_unique<Pendant>(glm::vec3(4.8f, 1.95f, 7.5f), glm::vec3(0.0f, 0.0f, 0.0f)));

    return objects;
}
