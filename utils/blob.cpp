/**
 * @file blob.cpp
 * @author
 * @brief
 * @version 0.1
 * @date 2022-03-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/blob.h"

std::vector<Object *> Blob::evaluate(const Scene &scene) const {
  Point marching_cube_origin(origin);
  int index = 0;
  double potential = -1;
  // std::vector<double> marching_potentials(8, 0);

  std::vector<Object *> triangles;

  for (int z = 0; z < nb_of_step; z++) {
    for (int y = 0; y < nb_of_step; y++) {
      for (int x = 0; x < nb_of_step; x++) {
        marching_cube_origin = origin + Vector(x * step, y * step, z * step);
        index = 0;

        for (int i = 0; i < 8; i++) {
          Point potential_point = marching_cube_origin + vertices[i];
          potential = scene.get_potential(potential_point);
          if (potential >= 1) index |= powers[i];
        }

        // Boucle pour créer nos triangles
        for (int i = 0; i < 15; i += 3) {
          if (edges_list[index][i] == -1) break;

          Point A = marching_cube_origin + edges[edges_list[index][i]];
          Point B = marching_cube_origin + edges[edges_list[index][i + 1]];
          Point C = marching_cube_origin + edges[edges_list[index][i + 2]];
          Triangle *triangle = new Triangle(A, C, B, default_material);
          triangles.push_back(triangle);
        }
      }
    }
  }

  return triangles;
}
