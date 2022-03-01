/**
 * @file object.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Object abstract class.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <optional>

#include "utils/color.h"
#include "utils/material.h"
#include "utils/ray.h"
#include "utils/scene.h"
#include "utils/vector.h"

/*
 * Implement an abstract class to manage objects. This class embed a Texture
 * Material and must held at least the 3 following pure virtual methods:
 * - the first to determine if a ray (a line expressed with a parametric
 * equation) intersects the object (returning the correct value of the parameter
 * in this case),
 * - the second to provide the normal of the surface at a specific position
 * on the surface,
 * - and the last one to determine the texture at the given point
 * on the surface (and delegate the process to T e x t u r e M a t e ri al)
 * Implement the class Sphere (derived from your object class) with the
 * implementation of (at least) the 3 previous methods.
 */

class Scene;
class Texture_Material;

// Abstract object class
class Object {
 public:
  virtual std::optional<Point> intersect(const Ray &ray) = 0;
  virtual Vector normal(const Point &point) = 0;
  virtual Color get_texture(const Point &point, const Ray &ray,
                            const Scene &scene) = 0;

  Texture_Material *material;
};
