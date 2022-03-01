/**
 * @file color.h
 * @author Adèle PLUQET and Adrien ANTON LUDWIG
 * @brief Color class.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <cstddef>

class Color {
 public:
  Color(size_t red, size_t green, size_t blue)
      : red(red), green(green), blue(blue) {}

  Color operator+(const Color &other) const {
    return Color(red + other.red, blue + other.blue, green + other.green);
  }

  Color operator*(const double &value) const {
    return Color(red * value, blue * value, green * value);
  }

  size_t red;
  size_t green;
  size_t blue;
};
