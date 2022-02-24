/**
 * @file ray.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Ray class methods.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/ray.h"

std::ostream &operator<<(std::ostream &os, const Ray &ray) {
  os << "origin: " << ray.origin << ", "
     << "direction: " << ray.direction;
  return os;
}
