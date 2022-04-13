/**
 * @file uniform_material.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Uniform material class.
 * @version 0.1
 * @date 2022-04-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <memory>

#include "utils/material.h"

class UniformMaterial : public Material {
 public:
  explicit UniformMaterial(std::shared_ptr<Texture> texture)
      : texture(texture) {}

  Color get(const Intersection &intersection, const Scene &scene,
            int reflection_index = 5) {
    return texture->get(intersection, scene);
  }

  std::shared_ptr<Texture> texture;
};
