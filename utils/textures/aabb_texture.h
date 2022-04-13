/**
 * @file aabb.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief AABB texture class.
 * @version 0.1
 * @date 2022-04-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <memory>

#include "utils/image.h"
#include "utils/material.h"

class AABBTexture : public Texture {
 public:
  AABBTexture(std::shared_ptr<Image> top, std::shared_ptr<Image> side,
              std::shared_ptr<Image> bottom)
      : top(top), side(side), bottom(bottom) {}

  Color get(const Intersection &intersection, const Scene &scene,
            int reflection_index = 5) override;

  std::shared_ptr<Image> top;
  std::shared_ptr<Image> side;
  std::shared_ptr<Image> bottom;
};
