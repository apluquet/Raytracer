/**
 * @file aabb.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief AABB texture class methods implementation.
 * @version 0.1
 * @date 2022-04-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/textures/aabb_texture.h"

#include "utils/objects/aabb.h"

Color AABBTexture::get(const Intersection &intersection, const Scene &scene) {
  AABB *object = dynamic_cast<AABB *>(intersection.object);

  if (!object)
    throw std::logic_error("AABBTexture should be assigned to AABB objects.");

  if (intersection.normal == object->normal_x_neg ||
      intersection.normal == object->normal_x_pos) {  // X sides
    int u = (intersection.point.y - object->min_vertex.y) /
            (object->max_vertex.y - object->min_vertex.y) * (side->width - 1);
    int v = (intersection.point.z - object->min_vertex.z) /
            (object->max_vertex.z - object->min_vertex.z) * (side->height - 1);

    if (intersection.normal == object->normal_x_neg)  // X min
      return side->get_pixel(side->width - 1 - u, v);
    else  // X max
      return side->get_pixel(u, v);
  } else if (intersection.normal == object->normal_y_neg ||
             intersection.normal == object->normal_y_pos) {  // Y sides
    int u = (intersection.point.x - object->min_vertex.x) /
            (object->max_vertex.x - object->min_vertex.x) * (side->width - 1);
    int v = (intersection.point.z - object->min_vertex.z) /
            (object->max_vertex.z - object->min_vertex.z) * (side->height - 1);

    if (intersection.normal == object->normal_y_neg)  // Y min
      return side->get_pixel(u, v);
    else  // Y max
      return side->get_pixel(side->width - 1 - u, v);
  } else if (intersection.normal == object->normal_z_pos) {  // Z top (== Z max)
    int u = (intersection.point.x - object->min_vertex.x) /
            (object->max_vertex.x - object->min_vertex.x) * (top->width - 1);
    int v = (intersection.point.y - object->min_vertex.y) /
            (object->max_vertex.y - object->min_vertex.y) * (top->height - 1);

    return top->get_pixel(u, v);
  } else if (intersection.normal ==
             object->normal_z_neg) {  // Z bottom (== Z min)
    int u = (intersection.point.x - object->min_vertex.x) /
            (object->max_vertex.x - object->min_vertex.x) * (bottom->width - 1);
    int v = (intersection.point.y - object->min_vertex.y) /
            (object->max_vertex.y - object->min_vertex.y) *
            (bottom->height - 1);

    return bottom->get_pixel(side->width - 1 - u, v);
  } else {
    // If we arrived here there is a problem.
    // 1) The operator == between Vectors (doubles) may be the problem.
    // 2) The intersection point may not be in the cube (wrong intersection).
    throw std::logic_error("Normal is not equal too any cube normal");
  }
}
