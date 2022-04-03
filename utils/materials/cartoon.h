/**
 * @file phong.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Cartoon material class.
 * @version 0.1
 * @date 2022-03-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "utils/material.h"

class CartoonMaterial : public Texture_Material {
 public:
  explicit CartoonMaterial(const Color &color, const double &ka,
                           const double &kd, const double &ks,
                           const double &alpha)
      : color(color), ka(ka), kd(kd), ks(ks), alpha(alpha) {
    kr = 0;
  }

  explicit CartoonMaterial(const Color &color, const double &ka,
                           const double &kd, const double &ks, const double &kr,
                           const double &alpha)
      : color(color), ka(ka), kd(kd), ks(ks), kr(kr), alpha(alpha) {}

  Color get(const Intersection &intersection, const Scene &scene,
            int reflection_index = 5);

  Color color;

  double ka;     // Composante ambiante
  double kd;     // Composante diffuse
  double ks;     // Composante spéculaire
  double kr;     // Composante réflection
  double alpha;  // Brilliance

 private:
  Color get_reflection(const Intersection &intersection, const Scene &scene,
                       int reflection_index);
  Color get_diffuse_and_specular(const Intersection &intersection,
                                 const Scene &scene);
};
