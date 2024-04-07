#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  float x;
  float y;
} vec2_t;


typedef struct {
  float x;
  float y;
  float z;
} vec3_t;

vec3_t vec3_rotate_z(vec3_t v, float angle);
vec3_t vec3_rotate_x(vec3_t v, float angle);
vec3_t vec3_rotate_y(vec3_t v, float angle);

vec2_t perspective_project_point(vec3_t point_3d);

float vec3_length(vec3_t v);
float vec2_length(vec2_t v);

//math for vec3
vec3_t vec3_add(vec3_t v, vec3_t v2);//not done
vec3_t vec3_subtract(vec3_t v, vec3_t v2);//not done
vec3_t vec3_multiply(vec3_t v, float scalar);//not done
vec3_t vec3_divide(vec3_t v, float scalar);//not done


//math for vec2
vec2_t vec2_add(vec2_t v, vec2_t v2);//not done
vec2_t vec2_subtract(vec2_t v, vec2_t v2);//not done
vec2_t vec2_multiply(vec2_t v, float scalar);//not done
vec2_t vec2_divide(vec2_t v, float scalar);//not done

//cross product vect3
vec3_t vec3_cross(vec3_t a, vec3_t b);
float vec3_dot(vec3_t a, vec3_t b);
float vec2_dot(vec2_t a, vec2_t b);

#endif