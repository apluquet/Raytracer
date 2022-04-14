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
#include <string>
#include <vector>

#include "utils/color.h"
#include "utils/libs/stb_image.h"

class Image {
 public:
  Image(std::size_t width, std::size_t height) : height(height), width(width) {
    my_image = std::vector(height, std::vector<Color>(width));
  }

  explicit Image(std::string path) { from_png(path); }

  // Enregistre l'image au format ppm
  void to_ppm(std::string filename, bool logging = true);

  // Récupère un pixel de notre image
  Color get_pixel(int x, int y);

 private:
  // Récupère l'image depuis un fichier png
  void from_png(std::string path);

 public:
  std::size_t height;
  std::size_t width;
  std::vector<std::vector<Color>> my_image;
};
