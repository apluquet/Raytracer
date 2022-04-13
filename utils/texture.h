/**
 * @file texture.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Texture class.
 * @version 0.1
 * @date 2022-04-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <stdint.h>

#include "utils/color.h"
#include "utils/intersection.h"
#include "utils/point.h"
#include "utils/scene.h"

class Scene;

class Texture {
 public:
  /**
   * @brief
   *
   * @param intersection : Contains :
   * - The point of the material for which to compute
   * - The ray that touched the point and asked for the texture.
   * @param scene : The scene object containing every object and light.
   * @return Color
   */
  virtual Color get(const Intersection &intersection, const Scene &scene) = 0;
};
