/**
 * @file object_loader.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Object loader functions prototype.
 * @version 0.1
 * @date 2022-03-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "utils/object.h"

namespace fs = std::filesystem;

// If material is nullptr, the color is imported from the material diffuse
// color.
std::vector<Object *> object_loader(const std::vector<std::string> &files,
                                    Texture_Material *material = nullptr);
