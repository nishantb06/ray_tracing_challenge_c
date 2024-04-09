# Ray Tracer Challenge : Implemented in C

## TODO
- Rename the Determinant New function to only Determinant, deprecate or delete the old hardcoded one
- How to make a function accept an unknown number of argumenst in c (Done) , (You cant pass an array instead)
- How to declare a variable in c whose type is unkwown, 
- https://developer.nvidia.com/blog/accelerated-ray-tracing-cuda/
- https://developer.nvidia.com/blog/optix-a-new-look-for-gpu-ray-tracing-in-film-and-design/
- look for a good folder structure, Done 
- each header file should have the definitions first then the declarations
- think how each function should accept values or references, and similary do they need to return new objects or manipulate existing ones
- all the header files in a separete folder, all tests in a different folder , Done
- the scripts that create visualisations at the end of each chapter in a separete folder, Done
- Makefile to run tests , Done
- and sync that with github actions
- comments for important function, about what they return and accept as arguments
- install and learn how to debug with [gdb](https://dev.to/jasonelwood/setup-gdb-on-macos-in-2020-489k)


-------
## DEFINITIONS

Sphere Sphere_(float radius, float id)
World* DefaultWorld()
Intersections* IntersectWorld(World *world, Ray *ray)