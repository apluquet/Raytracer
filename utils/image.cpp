/**
 * @file image.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Implementation of class Image
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "utils/image.h"

#include <iostream>

void Image::to_ppm() {
  std::ofstream ofs("my_image.ppm", std::ofstream::out);
  ofs << "P3 " << width << " " << height << " 255" << std::endl;
  for (std::size_t i = 0; i < height; i++) {
    for (std::size_t j = 0; j < width; j++)
      ofs << my_image[i][j].red << " " << my_image[i][j].green << " "
          << my_image[i][j].blue << " ";
    ofs << std::endl;
  }
  ofs.close();

  std::cout << "Write image : success !" << std::endl;
}

std::vector<uint8_t> Image::to_rgba_vector() {
  std::vector<uint8_t> rgba;
  uint8_t alpha = 0;  // Transparancy

  for (std::size_t i = 0; i < height; i++) {
    for (std::size_t j = 0; j < width; j++) {
      Color pixel_color = my_image[i][j];
      rgba.push_back(pixel_color.red);
      rgba.push_back(pixel_color.blue);
      rgba.push_back(pixel_color.green);
      rgba.push_back(alpha);
    }
  }

  return rgba;
}
