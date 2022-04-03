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
  {
    std::ofstream ofs("my_image.ppm", std::ofstream::out);
    ofs << "P3 " << width << " " << height << " 255" << std::endl;
    for (std::size_t i = 0; i < height; i++) {
      for (std::size_t j = 0; j < width; j++)
        ofs << my_image[i][j].getRedRgb() << " " << my_image[i][j].getGreenRgb()
            << " " << my_image[i][j].getBlueRgb() << " ";
      ofs << std::endl;
    }
    ofs.close();
  }

  std::cout << "Write image : success !" << std::endl;
}
