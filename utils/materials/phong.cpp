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

Color PhongMaterial::get(const Point &point, const Ray &ray,
                         const Scene &scene) {
  Color ambient = color * scene.ambientIntensity * ka;

  // I_d = i_d k_d (\vec L \cdot \vec N) = i_d k_d \cos \theta

  // See if we do not hit another object

  Color diffuse(0, 0, 0);

  Color specular(0, 0, 0);

  return ambient + diffuse + specular;
}
