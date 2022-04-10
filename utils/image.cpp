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

#define RGB_DEPTH 3

void Image::to_ppm() {
  {
    std::ofstream ofs("my_image.ppm", std::ofstream::out);
    ofs << "P3 " << width << " " << height << " 255" << std::endl;
    for (std::size_t i = 0; i < height; i++) {
      for (std::size_t j = 0; j < width; j++)
        ofs << my_image[i][j].getRedInt() << " " << my_image[i][j].getGreenInt()
            << " " << my_image[i][j].getBlueInt() << " ";
      ofs << std::endl;
    }
    ofs.close();
  }

  std::cout << "Write image : success !" << std::endl;
}

Color Image::get_pixel(int x, int y) {
  if (x >= height || y >= width) std::invalid_argument("Index out of bounds\n");
  return my_image[x][y];
}

void Image::from_png(std::string path) {
  int widthPNG, heightPNG, bpp;
  uint8_t* rgb_image =
      stbi_load(path.c_str(), &widthPNG, &heightPNG, &bpp, RGB_DEPTH);

  if (rgb_image == nullptr || widthPNG == 0 || heightPNG == 0)
    throw std::logic_error("Error loading image: " + path);

  height = heightPNG;
  width = widthPNG;

  for (int i = 0; i < height; i++) {
    std::vector<Color> line;
    for (int j = 0; j < width; j++) {
      int index = RGB_DEPTH * (i * width + j);
      Color color(rgb_image[index] / 255., rgb_image[index + 1] / 255.,
                  rgb_image[index + 2] / 255.);
      line.push_back(color);
    }
    my_image.push_back(line);
  }
  stbi_image_free(rgb_image);
}
