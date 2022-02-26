/**
 * @file camera.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Camera class methods.
 * @version 0.1
 * @date 2022-02-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/camera.h"

// (x,y) are coordinates in the image referential. (0,0) is the top left corner
// and (image.width, image.height), the bottom right corner. We use 'double'
// rather than 'int' to gain some granularity.
Ray Camera::cast_ray(const double &x, const double &y) {
  // Finds position in real world of pixel (x,y)

  Point ray_origin = image_right * x + image_down * y + image_origin;
  Vector ray_direction = (ray_origin - position).normalize();

  return Ray(ray_origin, ray_direction);
}
