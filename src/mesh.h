#ifndef MESH_H
#define MESH_H
#include "vector.h"
#include "triangle.h"

#define N_MESH_VERTICES 8 //8 corners

extern vec3_t mesh_vertices[N_MESH_VERTICES];

#define N_MESH_FACES 12 //6 sides, two triangles per side

extern face_t mesh_faces[N_MESH_FACES];

#endif