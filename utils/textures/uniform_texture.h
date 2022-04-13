/**
 * @file uniform_texture.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Uniform texture class.
 * @version 0.1
 * @date 2022-04-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "utils/texture.h"

class UniformTexture : public Texture {
 public:
  explicit UniformTexture(const Color &color) : color(color) {}

  Color get(const Intersection &intersection, const Scene &scene,
            int reflection_index = 5) {
    return color;
  }

  Color color;
};
