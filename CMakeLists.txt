cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 20)

# Notre projet est étiqueté hello
project(raytracer)



include_directories(${CMAKE_SOURCE_DIR})

# Crée des variables avec les fichiers à compiler
set(SRCS
    main.cpp
    utils/blob.cpp
    utils/camera.cpp
    utils/image.cpp
    utils/materials/phong.cpp
    utils/materials/cartoon.cpp
    utils/object_loader.cpp
    utils/objects/aabb.cpp
    utils/objects/sphere.cpp 
    utils/objects/triangle.cpp
    utils/ray.cpp
    utils/scene.cpp
    utils/textures/aabb_texture.cpp
    utils/vector.cpp
    )
    
set(HEADERS
    tinyobjloader/tiny_obj_loader.h
    utils/blob.h
    utils/camera.h
    utils/color.h 
    utils/image.h 
    utils/intersection.h
    utils/libs/stb_image.h
    utils/light.h
    utils/material.h
    utils/materials/cartoon.h
    utils/materials/phong.h
    utils/object.h
    utils/object_loader.h
    utils/objects/aabb.h
    utils/objects/sphere.h
    utils/objects/triangle.h
    utils/point.h 
    utils/ray.h
    utils/scene.h
    utils/textures/aabb_texture.h
    utils/vector.h
    )

add_compile_options(-g -O3 -march=native)
add_link_options(-pthread)
add_executable(raytracer ${SRCS} ${HEADERS})
