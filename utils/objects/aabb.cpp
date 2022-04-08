/**
 * @file bouding_box.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Bounding box class method implementation.
 * @version 0.1
 * @date 2022-04-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/objects/aabb.h"

#include <algorithm>
#include <utility>

std::optional<Intersection> AABB::intersect(const Ray &ray) {
  // Ray equation: r = O + t * D;
  // Face equation x min : min_vertex.x

  // Intersection ray / x_min face: t_min_x = (min_vertex.x - O.x) / D.x;

  // X
  Vector normal_min_x = normal_x_neg;
  Vector normal_max_x = normal_x_pos;
  double t_min_x = (min_vertex.x - ray.origin.x) / ray.direction.x;
  double t_max_x = (max_vertex.x - ray.origin.x) / ray.direction.x;

  if (t_max_x < t_min_x) {
    std::swap(t_min_x, t_max_x);
    std::swap(normal_min_x, normal_max_x);
  }

  // Y
  Vector normal_min_y = normal_y_neg;
  Vector normal_max_y = normal_y_pos;
  double t_min_y = (min_vertex.y - ray.origin.y) / ray.direction.y;
  double t_max_y = (max_vertex.y - ray.origin.y) / ray.direction.y;

  if (t_max_y < t_min_y) {
    std::swap(t_min_y, t_max_y);
    std::swap(normal_min_y, normal_max_y);
  }

  if (t_max_y < t_min_x || t_max_x < t_min_y) return std::nullopt;

  // t
  Vector normal_min = normal_min_x;
  Vector normal_max = normal_max_x;
  double t_min = t_min_x;
  double t_max = t_max_x;

  if (t_min < t_min_y) {
    t_min = t_min_y;
    normal_min = normal_min_y;
  }
  if (t_max_y < t_max) {
    t_max = t_max_y;
    normal_max = normal_max_y;
  }

  // Z
  Vector normal_min_z = normal_z_neg;
  Vector normal_max_z = normal_z_pos;
  double t_min_z = (min_vertex.z - ray.origin.z) / ray.direction.z;
  double t_max_z = (max_vertex.z - ray.origin.z) / ray.direction.z;

  if (t_max_z < t_min_z) {
    std::swap(t_min_z, t_max_z);
    std::swap(normal_min_z, normal_max_z);
  }

  if (t_max_z < t_min || t_max < t_min_z) return std::nullopt;

  // t
  if (t_min < t_min_z) {
    t_min = t_min_z;
    normal_min = normal_min_z;
  }

  if (t_max_z < t_max) {
    t_max = t_max_z;
    normal_max = normal_max_z;
  }

  // Check if the intersection is behind
  if (t_min < 0) {
    t_min = t_max;
    normal_min = normal_max;
  }

  if (t_max < 0) return std::nullopt;

  Point intersection_point = ray.origin + ray.direction * t_min;
  return Intersection(ray, intersection_point, normal_min, this);
}

Vector AABB::normal(const Point &point) {
  throw std::logic_error("Should not be used.");
}

Texture_Material *AABB::get_material() { return material; }

double AABB::get_potential(const Point &point) {
  throw std::logic_error("Not implemented yet.");
}

std::vector<Point> AABB::get_position() { return {min_vertex, max_vertex}; }
