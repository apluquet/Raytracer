cmake_minimum_required(VERSION 3.0)

set (CMAKE_CXX_STANDARD 17)

# Notre projet est étiqueté hello
project(raytracer)



include_directories(${CMAKE_SOURCE_DIR})

# Crée des variables avec les fichiers à compiler
set(SRCS
    main.cpp
    utils/image.cpp
    utils/objects/sphere.cpp 
    utils/ray.cpp
    utils/scene.cpp
    utils/vector.cpp
    utils/camera.cpp
    )
    
set(HEADERS
    gif-h/gif.h
    utils/camera.h
    utils/color.h 
    utils/image.h 
    utils/light.h
    utils/material.h
    utils/object.h
    utils/objects/sphere.h
    utils/point.h 
    utils/ray.h
    utils/scene.h
    utils/vector.h
    )

add_compile_options(-O3)
add_executable(raytracer ${SRCS} ${HEADERS})
