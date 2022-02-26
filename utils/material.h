/**
 * @file material.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Material classes.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef UTILS_MATERIAL_H_
#define UTILS_MATERIAL_H_

#include <stdint.h>

#include "utils/color.h"
#include "utils/point.h"

/*
 * Add an abstract class for Texture_Material with (at least) one pure
 * virtual method which provide all parameters for the texture and the material
 * (kd, ks...). This method take in argument, a position of a point on the
 * surface. Add the class: Uni form Tex ture (which derive from
 * Texture_Material). The implementation of the method will provide constant
 * parameters (kd, ks...) at every points of the surface.
 */

// ks : propriété de reflexion de la surface = composante spéculaire
// kd : les kd incluent la couleur = composante diffuse

/**
 * @brief Abstract material class.
 *
 */

class Texture_Material {
 public:
  virtual Color get(const Point &point) = 0;
};

class Uniform_Texture : public Texture_Material {
 public:
  Uniform_Texture(const double &a, const double &b) {}

  Color get(const Point &point) { return Color(1, 1, 1); }
};
/*
class Texture_Material {
 public:
  Texture_Material();

  virtual Color get(const Point &point);
};


class Uniform_Texture { //: public Texture_Material {
 public:
  Uniform_Texture(const double &kd, const double &ks) : kd(kd), ks(ks) {}

  Color get(const Point &point);

  double kd;
  double ks;
};*/

#endif  // UTILS_MATERIAL_H_
