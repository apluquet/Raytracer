/**
 * @file checkeredSphere.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Texture mapping material class implementation.
 * @version 0.1
 * @date 2022-04-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/textures/checkeredSphere.h"

#include <math.h>

#include <cmath>
#include <vector>

#include "utils/textures/sphereUtils.h"

// Returns the box for a generated checkered pattern
bool CheckeredSphere::getBox(double u, double v) {
  bool dark = 1;

  if (static_cast<int>(floor(u / widthBox)) % 2 == 1) dark = !dark;
  if (static_cast<int>(floor(v / heightBox)) % 2 == 1) dark = !dark;

  return dark;
}

Color CheckeredSphere::get(const Intersection &intersection, const Scene &scene,
                           int reflection_index) {
  Point flat = flatten3Dpoint(intersection.point,
                              intersection.object->get_position()[0]);

  // std::cout << "here\n";

  // Nice color example :
  // Color one(52. / 255, 235. / 255, 158. / 255);
  // Color two(235. / 255, 232. / 255, 52. / 255);

  if (getBox(flat.x, flat.y)) return one;
  return two;
}
