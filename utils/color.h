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
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

#define COLOR_MIN 0.
#define COLOR_MAX 1.
#define COLOR_INT_MIN 0
#define COLOR_INT_MAX 255

static bool isRgbDouble(double color) {
  return COLOR_MIN <= color && color <= COLOR_MAX;
}

static bool almostEqual(double a, double b) {
  return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
}

class Color {
 public:
  Color() : red(0), green(0), blue(0) {}

  Color(double red, double green, double blue)
      : red(red), green(green), blue(blue) {
    if (!isRgbDouble(red) || !isRgbDouble(green) || !isRgbDouble(blue)) {
      std::stringstream errorMessage;
      errorMessage << "To initialize a Color with integers, components should "
                      "be in [0.; 1.], got : "
                   << red << " " << green << " " << blue;
      throw std::logic_error(errorMessage.str());
    }
  }

  Color operator+(const Color &other) const {
    return Color(std::min(red + other.red, COLOR_MAX),
                 std::min(green + other.green, COLOR_MAX),
                 std::min(blue + other.blue, COLOR_MAX));
  }

  Color operator*(const Color &other) const {
    return Color(red * other.red, green * other.green, blue * other.blue);
  }

  Color operator*(const double &value) const {
    return Color(std::min(red * value, COLOR_MAX),
                 std::min(green * value, COLOR_MAX),
                 std::min(blue * value, COLOR_MAX));
  }

  Color operator==(const Color &other) const {
    return Color(almostEqual(red, other.red), almostEqual(green, other.green),
                 almostEqual(blue, other.blue));
  }

  int getRedInt() { return red * COLOR_INT_MAX; }
  int getGreenInt() { return green * COLOR_INT_MAX; }
  int getBlueInt() { return blue * COLOR_INT_MAX; }

  double red;
  double green;
  double blue;
};
