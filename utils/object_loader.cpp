/**
 * @file object_loader.cpp
 * @author Adèle PLUQUET and Adrien ANTON LUDWIG
 * @brief Object loader functions implementation.
 * @version 0.1
 * @date 2022-03-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "utils/object_loader.h"

#define TINYOBJLOADER_IMPLEMENTATION  // define this in only *one* .cc

#include "tinyobjloader/tiny_obj_loader.h"
#include "utils/materials/cartoon.h"
#include "utils/materials/phong.h"
#include "utils/objects/triangle.h"

static void object_parser(const std::string& inputfile,
                          tinyobj::ObjReader& reader) {
  tinyobj::ObjReaderConfig reader_config;

  if (!reader.ParseFromFile(inputfile, reader_config)) {
    if (!reader.Error().empty()) {
      std::cerr << "TinyObjReader: " << reader.Error();
    }
    exit(1);
  }

  if (!reader.Warning().empty()) {
    std::cout << "TinyObjReader: " << reader.Warning();
  }
}

std::vector<Object*> object_loader(const std::vector<std::string>& files,
                                   Texture_Material* material) {
  std::vector<Object*> objects;
  int last_size = 0;

  for (const std::string file : files) {
    tinyobj::ObjReader reader;
    object_parser(file, reader);

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    std::vector<Texture_Material*> our_materials;
    if (material == nullptr) {
      for (size_t i = 0; i < materials.size(); i++) {
        our_materials.push_back(new PhongMaterial(
            Color(materials[i].diffuse[0], materials[i].diffuse[1],
                  materials[i].diffuse[2]),
            0.2, 0.8, 0.3, 150));

        // CartoonMaterial(material.ambient, material.ambient,
        //  material.diffuse, material.specular, material.shininess)));
      }
    } else {
      // If we gave a metrial, we will use it istead of all the materials in the
      // .mtl.
      our_materials = std::vector(materials.size(), material);
    }

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
      // Loop over faces(polygon)
      size_t index_offset = 0;
      for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
        size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

        // Create Triangle objects
        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + 0];

        Point A(attrib.vertices[3 * size_t(idx.vertex_index) + 0],
                attrib.vertices[3 * size_t(idx.vertex_index) + 1],
                attrib.vertices[3 * size_t(idx.vertex_index) + 2]);

        Vector normal_A(attrib.normals[3 * size_t(idx.normal_index) + 0],
                        attrib.normals[3 * size_t(idx.normal_index) + 1],
                        attrib.normals[3 * size_t(idx.normal_index) + 2]);

        idx = shapes[s].mesh.indices[index_offset + 1];

        Point B(attrib.vertices[3 * size_t(idx.vertex_index) + 0],
                attrib.vertices[3 * size_t(idx.vertex_index) + 1],
                attrib.vertices[3 * size_t(idx.vertex_index) + 2]);
        Vector normal_B(attrib.normals[3 * size_t(idx.normal_index) + 0],
                        attrib.normals[3 * size_t(idx.normal_index) + 1],
                        attrib.normals[3 * size_t(idx.normal_index) + 2]);

        idx = shapes[s].mesh.indices[index_offset + 2];

        Point C(attrib.vertices[3 * size_t(idx.vertex_index) + 0],
                attrib.vertices[3 * size_t(idx.vertex_index) + 1],
                attrib.vertices[3 * size_t(idx.vertex_index) + 2]);
        Vector normal_C(attrib.normals[3 * size_t(idx.normal_index) + 0],
                        attrib.normals[3 * size_t(idx.normal_index) + 1],
                        attrib.normals[3 * size_t(idx.normal_index) + 2]);

        // Material
        int material_id = shapes[s].mesh.material_ids[f];
        std::cout << materials[material_id].name << std::endl;

        objects.push_back(new Triangle(A, B, C, normal_A, normal_B, normal_C,
                                       our_materials[material_id]));

        index_offset += fv;
      }
    }

    std::cout << file << ": " << objects.size() - last_size << " triangles"
              << std::endl;
    last_size = objects.size();
  }

  return objects;
}
