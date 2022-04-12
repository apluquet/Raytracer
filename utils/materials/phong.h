/**
 * @file phong.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Phong material class.
 * @version 0.1
 * @date 2022-02-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <memory>

#include "utils/material.h"

class PhongMaterial : public Material {
 public:
  explicit PhongMaterial(std::shared_ptr<Texture> texture, const double &ka,
                         const double &kd, const double &ks,
                         const double &alpha)
      : texture(texture), ka(ka), kd(kd), ks(ks), alpha(alpha) {
    kr = 0;
  }

  explicit PhongMaterial(std::shared_ptr<Texture> texture, const double &ka,
                         const double &kd, const double &ks, const double &kr,
                         const double &alpha)
      : ka(ka), kd(kd), ks(ks), kr(kr), alpha(alpha) {}

  Color get(const Intersection &intersection, const Scene &scene,
            int reflection_index = 5);

  std::shared_ptr<Texture> texture;
  double ka;     // Composante ambiante
  double kd;     // Composante diffuse
  double ks;     // Composante spéculaire
  double kr;     // Composante réflection
  double alpha;  // Brilliance

 private:
  Color get_reflection(const Intersection &intersection, const Scene &scene,
                       const Color &color, int reflection_index);
  Color get_diffuse_and_specular(const Intersection &intersection,
                                 const Scene &scene, const Color &color);
};
