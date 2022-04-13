/**
 * @file cartoon.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Cartoon material class implementation.
 * @version 0.1
 * @date 2022-03-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/materials/cartoon.h"

#include <algorithm>

#include "utils/scene.h"

Color CartoonMaterial::get_reflection(const Intersection &intersection,
                                      const Scene &scene,
                                      int reflection_index) {
  return Color(0, 0, 0);
}

std::optional<Color> CartoonMaterial::get_outline(
    const Intersection &intersection, const Scene &scene) {
  double shadow_thick = 0.3;
  double light_thick = 0.2;

  // Light direction
  Vector light_vector = scene.lights[0]->get_position() - intersection.point;
  Vector light_direction = (light_vector).normalize();

  double camera_alignment = -intersection.ray.direction * intersection.normal;
  double light_alignment = std::max(0., intersection.normal * light_direction);

  double interpolation =
      shadow_thick + (light_thick - shadow_thick) * light_alignment;

  if (camera_alignment < interpolation)
    return scene.lights[0]->get_color() * outline_color;
  return std::nullopt;
}

Color CartoonMaterial::get_diffuse_and_specular(
    const Intersection &intersection, const Scene &scene) {
  Vector light_vector;
  Vector light_direction;
  Vector light_reflection;
  Ray light_ray;
  double cos_theta;  // Angle between light and normal
  double cos_omega;  // Angle between ray incident and reflection
  Color diffuse;
  Color specular;
  std::optional<Intersection> intersect_object;

  for (Light *light : scene.lights) {
    // Compute ray from intersection to light
    light_vector = light->get_position() - intersection.point;
    light_direction = (light_vector).normalize();
    light_ray =
        Ray(intersection.point + light_direction * 0.00001, light_direction);

    // See if we do not hit another object
    intersect_object = scene.intersectObject(light_ray, light_vector.length());

    if (intersect_object.has_value()) {
      double distance =
          (intersect_object.value().point - intersection.point).length();
      if (distance < light_vector.length()) continue;
    }

    cos_theta = light_direction * intersection.normal;
    if (cos_theta < 0) cos_theta = 0;
    light_reflection = intersection.normal * 2 * cos_theta - light_direction;
    cos_omega = light_reflection * -intersection.ray.direction;
    if (cos_omega < 0) cos_omega = 0;

    Color point_color = light->get_color() * color;

    // DIFFUSE
    // I_d = i_d k_d (L.N) = i_d k_d cos(theta)
    diffuse = diffuse + point_color * cos_theta * light->get_intensity() * kd;

    // SPECULAR
    // I_s = i_s * k_s * (R.V)^α = i_s * k_s * cos^α(Ω)
    // Le rayon réfléchi R se déduit par la relation  :
    // R = 2 * (N.L) * N - L = 2 * cos(theta) * N - L
    specular = specular + light->get_color() * light->get_intensity() *
                              pow(cos_omega, alpha) * ks;
  }

  // Returns a white color
  if (specular.red + specular.green + specular.blue > 0.3)
    return Color(1, 1, 1);

  // double color_mean = (diffuse.red + diffuse.green + diffuse.blue) / 3;
  double color_mean =
      std::max(diffuse.red, std::max(diffuse.blue, diffuse.green));
  // Computes the color with the number of shades
  double step = 1. / n_shades;
  for (int i = 1; i < n_shades; i++) {
    if (color_mean < (i * step / 7)) return color * Color(1, 1, 1) * (i * step);
  }
  return color;
}

Color CartoonMaterial::get(const Intersection &intersection, const Scene &scene,
                           int reflection_index) {
  // AMBIENT
  Color ambient = color * scene.ambientIntensity * ka;

  std::optional<Color> outline = get_outline(intersection, scene);
  if (outline.has_value()) return outline.value();
  return ambient + get_diffuse_and_specular(intersection, scene) +
         get_reflection(intersection, scene, reflection_index);
}
