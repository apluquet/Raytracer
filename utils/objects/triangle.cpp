/**
 * @file sphere.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Sphere class.
 * @version 0.1
 * @date 2022-03-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/objects/triangle.h"

#include <vector>

std::optional<Intersection> Triangle::intersect(const Ray &ray) {
  Vector OA = A - ray.origin;
  Vector OB = B - ray.origin;
  Vector OC = C - ray.origin;

  double mat[3][3] = {
      {OA.x, OB.x, OC.x},
      {OA.y, OB.y, OC.y},
      {OA.z, OB.z, OC.z},
  };

  double det = 0;  // Determinant
  for (int i = 0; i < 3; i++)
    det += mat[0][i] * (mat[1][(i + 1) % 3] * mat[2][(i + 2) % 3] -
                        mat[1][(i + 2) % 3] * mat[2][(i + 1) % 3]);

  if (det == 0.) return std::nullopt;

  double mat_inv[3][3];

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) {
      int i2 = (i + 1) % 3;
      int i3 = (i + 2) % 3;
      int j2 = (j + 1) % 3;
      int j3 = (j + 2) % 3;

      mat_inv[j][i] =
          (mat[i2][j2] * mat[i3][j3] - mat[i2][j3] * mat[i3][j2]) / det;
    }

  double coefs[3] = {0, 0, 0};

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) coefs[i] += mat_inv[i][j] * ray.direction[j];

  double alpha = coefs[0];
  double beta = coefs[1];
  double gamma = coefs[2];

  if (alpha < 0 || beta < 0 || gamma < 0) return std::nullopt;

  Vector OG = ray.direction / (alpha + beta + gamma);
  Point G = OG + ray.origin;

  Intersection intersection(ray, G, normal(G), this);

  return intersection;
}

Vector Triangle::normal(const Point &point) {
  if (normal_A == normal_B && normal_B == normal_C)
    // Computed hard normal, triangle is flat
    return normal_A;

  // Barycentric coordinates
  double ABCarea = (((B - A) ^ (C - A)).length()) / 2;
  double CAParea = (((A - C) ^ (point - C)).length()) / 2;
  double ABParea = (((B - A) ^ (point - A)).length()) / 2;
  double BCParea = (((C - B) ^ (point - B)).length()) / 2;

  double u = CAParea / ABCarea;
  double v = ABParea / ABCarea;
  double w = BCParea / ABCarea;

  Vector normal = normal_A * w + normal_B * u + normal_C * v;
  return normal;
}

Texture_Material *Triangle::get_material() { return material; }

double Triangle::get_potential(const Point &point) { return 0; }

std::vector<Point> Triangle::get_position() { return {A, B, C}; }
