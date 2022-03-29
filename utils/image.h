/**
 * @file image.h
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Definition of class image
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <cstdio>
#include <fstream>
#include <vector>

#include "utils/color.h"

class Image {
 public:
  Image(std::size_t width, std::size_t height) : height(height), width(width) {
    my_image = std::vector(height, std::vector<Color>(width));
  }

  // Enregistre l'image au format ppm
  void to_ppm();

  std::size_t height;
  std::size_t width;
  std::vector<std::vector<Color>> my_image;
};
