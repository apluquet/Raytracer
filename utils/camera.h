/**
 * @file camera.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Camera class.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "utils/image.h"
#include "utils/point.h"
#include "utils/ray.h"
#include "utils/vector.h"

#define PI 3.14159265

class Camera {
 public:
  Camera(const Point &position, const Vector &direction, const Vector &up,
         const double &z_min, const float &view_angle_x,
         const float &view_angle_y, const Image &image)
      : position(position) {
    // demi-height and demi-width are respectively the half of the height
    // and width of the image plan.
    double demi_height = tan((view_angle_y / 2) * PI / 180) * z_min;
    double demi_width = tan((view_angle_x / 2) * PI / 180) * z_min;

    // Size of a pixel "in the real world"
    double pixel_height = (2 * demi_height) / image.height;
    double pixel_width = (2 * demi_width) / image.width;

    // Compute unit vectors of the image plan
    image_right = (direction ^ up).normalize() * pixel_width;
    image_down = (-up).normalize() * pixel_height;

    // TOp left corner of our image
    image_origin = position + direction.normalize() * z_min -
                   image_down * image.height / 2 -
                   image_right * image.width / 2;
  }

  Ray cast_ray(const double &x, const double &y);

  Point position;      // Camera position
  Point image_origin;  // Top left corner of our image
  Vector image_down;   // Unit vector for a pixel height
  Vector image_right;  // Unit vecto for a pixel width
};
