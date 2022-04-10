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

Color AABBTexture::get(const Intersection &intersection, const Scene &scene,
                       int reflection_index) {
  AABB *object = dynamic_cast<AABB *>(intersection.object);

  if (!object)
    throw std::logic_error("AABBTexture should be assigned to AABB objects.");

  if (intersection.normal == object->normal_x_neg ||
      intersection.normal == object->normal_x_pos) {
    int u = (intersection.point.y - object->min_vertex.y) /
            (object->max_vertex.y - object->min_vertex.y) * (side->width - 1);
    int v = (intersection.point.z - object->min_vertex.z) /
            (object->max_vertex.z - object->min_vertex.z) * (side->height - 1);
    return side->get_pixel(side->height - 1 - v, u);
  } else if (intersection.normal == object->normal_y_neg ||
             intersection.normal == object->normal_y_pos) {
    return Color(1, 0, 0);
  } else {
    return Color(0, 1, 0);
  }
}
