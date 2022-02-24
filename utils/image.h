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

#ifndef UTILS_IMAGE_H_
#define UTILS_IMAGE_H_

#include <cstdio>
#include <fstream>
#include <vector>

#include "utils/color.h"

class Image {
 public:
  Image(std::size_t width, std::size_t height) : height(height), width(width) {
    Color black = Color(50, 20, 250);
    Color red = Color(175, 0, 40);
    for (std::size_t i = 0; i < height; i++) {
      std::vector<Color> line;
      for (std::size_t j = 0; j < width; j++)
        ((j + i) % 2 == 0) ? line.push_back(black) : line.push_back(red);
      my_image.push_back(line);
    }
  }

  // Enregistre l'image au format ppm
  void to_ppm();

  std::size_t height;
  std::size_t width;
  std::vector<std::vector<Color>> my_image;
};

#endif  // UTILS_IMAGE_H_
