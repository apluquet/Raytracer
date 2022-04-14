# Raytracer

A ratracer realized in the framework of this course.

## Realizations

![Lofi girl cartoon](images/lofi_girl_cartoon.png)
![Minecraft](images/minecraft.png)

## Features :

* Objects available : sphere, triangle, Axis Aligned Bounding Box (AABB)
* Phong shader
* Reflection
* Blobs (metaballs)
* Smooth triangles
* Multithreading (CPU)
* Cartoon shader
* Object loader (.obj & .mtl)
* UV mapping : AABB and sphere

See TODO.md for further improvement ideas.

## Usage

```
$ mkdir build && cd build`
$ cmake ..`
$ make -j`
$ ./raytracer` 
```

And follow the USAGE message.
