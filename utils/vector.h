/**
 * @file vector.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Vector class.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef UTILS_VECTOR_H_
#define UTILS_VECTOR_H_

#include <math.h>

#include <iostream>

class Vector {
 public:
  Vector(const double &x, const double &y, const double &z)
      : x(x), y(y), z(z) {}

  Vector operator*(const double &value) const;
  Vector operator/(const double &value) const;
  double operator*(const Vector &other) const;  // dot product
  Vector operator^(const Vector &other) const;  // cross product
  Vector operator-(const Vector &other) const;
  Vector operator+(const Vector &other) const;
  double length() const;
  Vector normalize(const Vector &vector) const;

  friend std::ostream &operator<<(std::ostream &os, Vector &vector);

  double x;
  double y;
  double z;
};

#endif  // UTILS_VECTOR_H_
