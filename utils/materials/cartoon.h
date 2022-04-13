/**
 * @file cartoon.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Cartoon material class.
 * @version 0.1
 * @date 2022-03-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <memory>

#include "utils/material.h"

class CartoonMaterial : public Material {
 public:
  explicit CartoonMaterial(std::shared_ptr<Texture> texture, const double &ka,
                           const double &kd, const double &ks,
                           const double &alpha, int n_shades = 2)
      : texture(texture),
        ka(ka),
        kd(kd),
        ks(ks),
        alpha(alpha),
        n_shades(n_shades) {
    kr = 0;
  }

  explicit CartoonMaterial(std::shared_ptr<Texture> texture, const double &ka,
                           const double &kd, const double &ks, const double &kr,
                           const double &alpha, int n_shades = 2,
                           const Color &outline_color = Color(0, 0, 0))
      : texture(texture),
        ka(ka),
        kd(kd),
        ks(ks),
        kr(kr),
        alpha(alpha),
        n_shades(n_shades),
        outline_color(outline_color) {}

  Color get(const Intersection &intersection, const Scene &scene,
            int reflection_index = 5);

  Color outline_color;

  std::shared_ptr<Texture> texture;
  double ka;     // Composante ambiante
  double kd;     // Composante diffuse
  double ks;     // Composante spéculaire
  double kr;     // Composante réflection
  double alpha;  // Brilliance
  int n_shades;  // Nombre de nuances possibles par couleur.

 private:
  Color get_reflection(const Intersection &intersection, const Scene &scene,
                       int reflection_index);
  Color get_diffuse_and_specular(const Intersection &intersection,
                                 const Scene &scene, const Color &color);
  std::optional<Color> get_outline(const Intersection &intersection,
                                   const Scene &scene);
};
