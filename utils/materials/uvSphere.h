/**
 * @file phong.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Texture mapping material class implementation.
 * @version 0.1
 * @date 2022-04-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "utils/material.h"

class UVSphere : public Texture_Material {
 public:
  explicit UVSphere(const Image &my_texture) : my_texture(my_texture) {}

  Color get(const Intersection &intersection, const Scene &scene,
            int reflection_index = 5);

  Image my_texture;
};
