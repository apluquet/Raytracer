Split Scene.intersectObject in two functions and move distance check from Phong.get_texture().
Compute radius^2 in Sphere constructor rather than at every intersection.
Rename Texture_Material and Uniform_Texture.
Reflection
Scene loader (gltf)
Multithreading
Options parser (resolution, .obj file, )
Coverage analysis (and optimisation)
Refactor file structure (create folders, rename 'utils')
Retrieve material from .mtl (see tinyobjloader github )
Change color definition ? Use 0. -> 1. instead of 0 -> 255 ?
Normal shading: compute triangle normal using barycentric coordinates