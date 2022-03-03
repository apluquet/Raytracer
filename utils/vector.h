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

#pragma once

#include <math.h>

#include <iostream>

class Vector {
 public:
  Vector() : x(0), y(0), z(0) {}
  Vector(const double &x, const double &y, const double &z)
      : x(x), y(y), z(z) {}

  Vector operator*(const double &value) const;
  Vector operator/(const double &value) const;
  double operator*(const Vector &other) const;  // dot product
  Vector operator^(const Vector &other) const;  // cross product
  Vector operator-(const Vector &other) const;
  Vector operator+(const Vector &other) const;
  Vector operator-() const;
  double length() const;
  Vector normalize() const;

  friend std::ostream &operator<<(std::ostream &os, Vector &vector);
  friend std::ostream &operator<<(std::ostream &os, const Vector &vector);

  double x;
  double y;
  double z;
};
