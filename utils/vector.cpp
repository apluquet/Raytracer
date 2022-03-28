/**
 * @file vector.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Vector class methods.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/vector.h"

#include <stdexcept>

Vector Vector::operator*(const double &value) const {
  double new_x = x * value;
  double new_y = y * value;
  double new_z = z * value;
  return Vector(new_x, new_y, new_z);
}

Vector Vector::operator/(const double &value) const {
  double new_x = x / value;
  double new_y = y / value;
  double new_z = z / value;
  return Vector(new_x, new_y, new_z);
}

double Vector::operator*(const Vector &other) const {
  return x * other.x + y * other.y + z * other.z;
}

Vector Vector::operator^(const Vector &other) const {
  double new_x = y * other.z - z * other.y;
  double new_y = z * other.x - x * other.z;
  double new_z = x * other.y - y * other.x;
  return Vector(new_x, new_y, new_z);
}

Vector Vector::operator-(const Vector &other) const {
  double new_x = x - other.x;
  double new_y = y - other.y;
  double new_z = z - other.z;
  return Vector(new_x, new_y, new_z);
}

Vector Vector::operator+(const Vector &other) const {
  double new_x = x + other.x;
  double new_y = y + other.y;
  double new_z = z + other.z;
  return Vector(new_x, new_y, new_z);
}

bool Vector::operator==(const Vector &other) const {
  return (x == other.x && y == other.y && z == other.z);
}

Vector Vector::operator-() const { return Vector(-x, -y, -z); }

double Vector::length() const { return sqrt(x * x + y * y + z * z); }

Vector Vector::normalize() const { return *this / this->length(); }

double Vector::operator[](const int &index) const {
  switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      throw std::out_of_range("Vector index should be 0, 1  or 2.");
  }
}

std::ostream &operator<<(std::ostream &os, Vector &vector) {
  os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
  return os;
}

std::ostream &operator<<(std::ostream &os, const Vector &vector) {
  os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
  return os;
}
