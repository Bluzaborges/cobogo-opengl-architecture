#pragma once

#include <memory>
#include <vector>

#include <Block.h>

std::vector<Block> buildFloor();
std::vector<Block> buildWalls();
std::vector<std::unique_ptr<Object>> buildObjects();
