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

#include <utility>
#include <vector>

// https://viclw17.github.io/2018/07/16/raytracing-ray-sphere-intersection/
// Sphere : dot((P - C), (P - C)) = r²
// Ray : p(t) = O + tD
std::optional<Intersection> Sphere::intersect(const Ray &ray) {
  if (round(ray.direction.length()) != 1) throw;
  // else a = ray.direction * ray.direction = 1 * 1 * cos(0) = 1

  Vector diff = ray.origin - center;

  double b = ray.direction * 2 * diff;
  double c = diff * diff - radius * radius;

  double discriminant = b * b - 4 * c;

  double t0, t1;

  if (discriminant < 0) {  // there is no solution
    return std::nullopt;
  } else if (discriminant == 0) {  // one solution
    t0 = t1 = -0.5 * b;
  } else {  // two solutions
    double q = (b > 0) ? -0.5 * (b + sqrt(discriminant))
                       : -0.5 * (b - sqrt(discriminant));
    t0 = q;
    t1 = c / q;
    if (t1 < t0) std::swap(t0, t1);  // Sort t1 and t2
  }

  if (t0 < 0) {                       // t0 is behind the ray
    if (t1 < 0) return std::nullopt;  // t1 is also behind
    t0 = t1;                          // t1 is in front of the ray
  }

  Point intersection_point = ray.origin + ray.direction * t0;

  Intersection intersection(ray, intersection_point, normal(intersection_point),
                            this);

  return intersection;
}

Vector Sphere::normal(const Point &point) { return point - center; }

Color Sphere::get_texture(const Intersection &intersection,
                          const Scene &scene) {
  return material->get(intersection, scene);
}

double Sphere::get_potential(const Point &point) {
  return (point - center).length() < radius;
}

std::vector<Point> Sphere::get_position() { return {center}; }
