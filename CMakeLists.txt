cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté hello
project(raytracer)

# Crée des variables avec les fichiers à compiler
set(SRCS
    main.cpp
    utils/image.cpp
    )
    
set(HEADERS
    utils/color.h 
    utils/image.h 
    utils/point.h 
    utils/vector.h
    )

add_executable(raytracer ${SRCS} ${HEADERS})
