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

#include <math.h>

#include <algorithm>
#include <cstddef>

class Color {
 public:
  Color() : red(0), green(0), blue(0) {}
  Color(size_t red, size_t green, size_t blue)
      : red(red), green(green), blue(blue) {}

  Color operator+(const Color &other) const {
    size_t max = 255;
    return Color(std::min(red + other.red, max),
                 std::min(green + other.green, max),
                 std::min(blue + other.blue, max));
  }

  Color operator*(const Color &other) const {
    return Color(red * other.red, green * other.green, blue * other.blue);
  }

  Color operator*(const double &value) const {
    return Color(red * value, green * value, blue * value);
  }

  Color operator==(const Color &other) const {
    return Color(red == other.red, green == other.green, blue == other.green);
  }

  size_t red;
  size_t green;
  size_t blue;
};
