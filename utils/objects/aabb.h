/**
 * @file bouding_box.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Bounding box class.
 * @version 0.1
 * @date 2022-04-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <vector>

#include "utils/object.h"
#include "utils/point.h"
#include "utils/ray.h"

class AABB : public Object {
 public:
  AABB() {}
  AABB(const Point &min_vertex, const Point &max_vertex, Material *material)
      : min_vertex(min_vertex), max_vertex(max_vertex), material(material) {}

  std::optional<Intersection> intersect(const Ray &ray) override;
  Vector normal(const Point &point) override;
  Material *get_material() override;
  double get_potential(const Point &point) override;
  std::vector<Point> get_position() override;

  Point min_vertex;
  Point max_vertex;
  Material *material;
  Vector normal_x_neg = Vector(-1, 0, 0);
  Vector normal_x_pos = Vector(1, 0, 0);
  Vector normal_y_neg = Vector(0, -1, 0);
  Vector normal_y_pos = Vector(0, 1, 0);
  Vector normal_z_neg = Vector(0, 0, -1);
  Vector normal_z_pos = Vector(0, 0, 1);
};
