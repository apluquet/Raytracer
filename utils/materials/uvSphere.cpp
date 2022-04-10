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

#include "utils/materials/uvSphere.h"

#include <math.h>

#include <cmath>

#define PI 3.14159265

// Returns the box for a generated checkered pattern
static bool getBox(double u, double v, int width, int height) {
  double height_box = 1. / height;
  double width_box = 1. / width;

  bool dark = 1;

  if (static_cast<int>(floor(u / width_box)) % 2 == 1) dark = !dark;
  if (static_cast<int>(floor(v / height_box)) % 2 == 1) dark = !dark;

  return dark;
}

static Point flatten3Dpoint(const Point &point3D, const Point &center) {
  // Azimuthal angle increasing clockwise
  double theta = atan2(point3D.x, point3D.z);

  // Vector from sphere center to intersection point
  Vector vec = point3D - center;
  double radius = vec.length();

  // Polar angle
  double phi = acos(point3D.y / radius);

  double raw_u = theta / (2 * PI);
  double u = 1 - (raw_u + 0.5);
  double v = 1 - phi / PI;

  return Point(u, v, 0);
}

Color UVSphere::get(const Intersection &intersection, const Scene &scene,
                    int reflection_index) {
  Color one(52. / 255, 235. / 255, 158. / 255);
  Color two(235. / 255, 232. / 255, 52. / 255);

  Point flat = flatten3Dpoint(intersection.point,
                              intersection.object->get_position()[0]);

  if (getBox(flat.x, flat.y, 2000, 1000)) return one;
  return two;

  /* std::cout << "___________________________________\n";
  std::cout << getBox(0, 0, 2, 2) << std::endl;
  std::cout << getBox(0.5, 0, 2, 2) << std::endl;
  std::cout << getBox(0, 0.5, 2, 2) << std::endl;
  std::cout << getBox(0.5, 0.5, 2, 2) << std::endl;
  std::cout << getBox(1, 1, 2, 2) << std::endl; */
}
