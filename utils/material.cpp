/**
 * @file material.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Implementation of class material
 * @version 0.1
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/material.h"

Color Uniform_Texture::get(const Intersection &intersection,
                           const Scene &scene) {
  return color;
}
