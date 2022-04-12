/**
 * @file uvSphere.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Texture mapping material class implementation.
 * @version 0.1
 * @date 2022-04-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/materials/uvSphere.h"

#include <math.h>

#include <cmath>
#include <vector>

#include "utils/materials/sphereUtils.h"

Color UVSphere::getPixel(double u, double v, int width, int height) {
  u = floor(u * (width - 1));
  v = floor(v * (height - 1));

  return my_texture->get_pixel(v, u);
}

Color UVSphere::get(const Intersection &intersection, const Scene &scene,
                    int reflection_index) {
  // Point flat = flatten3Dpoint(intersection.point,
  //                            intersection.object->get_position()[0]);

  // return getPixel(flat.x, flat.y, my_texture->width, my_texture->height);
  return Color(0, 0, 0);
}
