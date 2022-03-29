/**
 * @file phong.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Phong material class implementation.
 * @version 0.1
 * @date 2022-02-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/materials/phong.h"

#include "utils/scene.h"

Color PhongMaterial::get_reflection(const Intersection &intersection,
                                    const Scene &scene, int reflection_index) {
  Color reflection_color;
  if (reflection_index > 0 && kr > 0.0001) {
    // R = I - 2(N.I)N
    Vector reflection_vector =
        intersection.ray.direction -
        intersection.normal * 2 *
            (intersection.normal * intersection.ray.direction);

    reflection_vector = reflection_vector.normalize();

    Ray reflection_ray(intersection.point + reflection_vector * 0.00001,
                       reflection_vector);
    std::optional<Intersection> reflection_intersection =
        scene.intersectObject(reflection_ray);

    if (reflection_intersection.has_value())
      reflection_color =
          reflection_intersection.value().object->get_material()->get(
              reflection_intersection.value(), scene, reflection_index - 1) *
          kr;
    else
      reflection_color = scene.backgroundColor * kr;
  }

  return reflection_color;
}

Color PhongMaterial::get_diffuse_and_specular(const Intersection &intersection,
                                              const Scene &scene) {
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

    Color point_color = Color(light->get_color().red / 255. * color.red,
                              light->get_color().green / 255. * color.green,
                              light->get_color().blue / 255. * color.blue);

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

  return diffuse + specular;
}

Color PhongMaterial::get(const Intersection &intersection, const Scene &scene,
                         int reflection_index) {
  // AMBIENT
  Color ambient = color * scene.ambientIntensity * ka;

  return ambient + get_diffuse_and_specular(intersection, scene) +
         get_reflection(intersection, scene, reflection_index);
}
