/**
 * @file sphere.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Sphere class methods.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/objects/sphere.h"

// https://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/
// Sphere : dot((P - C), (P - C)) = r²
// Ray : p(t) = O + tD
std::optional<Point> Sphere::intersect(const Ray &ray) {
  Vector diff = ray.origin - center;
  double a = ray.direction * ray.direction;
  double b = ray.direction * 2 * diff;
  double c = diff * diff - radius * radius;
  double discriminant = b * b - 4 * a * c;

  if (discriminant < 0) return std::nullopt;

  double sqrt_discriminant = sqrt(discriminant);
  double t = -b - sqrt_discriminant / 2 * a;

  if (t < 0) t = -b + sqrt_discriminant / 2 * a;

  Point intersection = ray.origin + ray.direction * t;

  return intersection;
}

Vector Sphere::normal(const Point &point) { return point - center; }

Color Sphere::get_texture(const Point &point) { return material.get(point); }
