#include "vector.h"
#include <math.h>

vec3_t vec3_rotate_z(vec3_t v, float angle)
{
  vec3_t rotated_vector = {
    .x = v.x * cos(angle) - v.y * sin(angle),
    .y = v.x * sin(angle) + v.y * cos(angle),
    .z = v.z
  };
  return rotated_vector;
}

  vec3_t vec3_rotate_y(vec3_t v, float angle)
{
  vec3_t rotated_vector = {
    .x = v.x * cos(angle) - v.z * sin(angle),
    .y = v.y,
    .z = v.x * sin(angle) + v.z * cos(angle)
  };
  return rotated_vector;
}

vec3_t vec3_rotate_x(vec3_t v, float angle)
{
  vec3_t rotated_vector = {
    .x = v.x,
    .y = v.y * cos(angle) - v.z * sin(angle),
    .z = v.y * sin(angle) + v.z * cos(angle)
  };
  return rotated_vector;
}

//length

float vec2_length(vec2_t v)
{
	float length;
	
	length = sqrt((v.x*v.x) + (v.y*v.y));
	return length;
}

float vec3_length(vec3_t v)
{
  float length;

  length = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return length;
}

//add
vec3_t vec3_add(vec3_t v, vec3_t v2){
  vec3_t added = {
    .x = (v.x)+(v2.x),
    .y = (v.y)+(v2.y),
    .z = (v.z)+(v2.z)
  };
  return added;
}

vec2_t vec2_add(vec2_t v, vec2_t v2){
  vec2_t added = {
    .x = (v.x)+(v2.x),
    .y = (v.y)+(v2.y)
  };
  return added;
}

//subtract

vec3_t vec3_subtract(vec3_t v, vec3_t v2){
  vec3_t subtracted = {
    .x = (v.x)-(v2.x),
    .y = (v.y)-(v2.y),
    .z = (v.z)-(v2.z)
  };
  return subtracted;
}

vec2_t vec2_subtract(vec2_t v, vec2_t v2){
  vec2_t subtracted = {
    .x = (v.x)-(v2.x),
    .y = (v.y)-(v2.y)
  };
  return subtracted;
}

//multiply
vec3_t vec3_multiply(vec3_t v, float scalar){
  vec3_t multiplied = {
    .x = v.x*scalar,
    .y = v.y*scalar,
    .z = v.z*scalar
  };
  return multiplied;
}

vec2_t vec2_multiply(vec2_t v, float scalar){
  vec2_t multiplied = {
    .x = v.x*scalar,
    .y = v.y*scalar
  };
  return multiplied;
}

//divide
vec3_t vec3_divide(vec3_t v, float scalar){
  vec3_t divided = {
    .x = v.x / scalar,
    .y = v.y / scalar,
    .z = v.z / scalar
  };
  return divided;
}

vec2_t vec2_divide(vec2_t v, float scalar){
  vec2_t divided = {
    .x = v.x / scalar,
    .y = v.y / scalar
  };
  return divided;
}

vec3_t vec3_cross(vec3_t a, vec3_t b)
{
  vec3_t result = {
    .x = a.y * b.z - a.z * b.y,
    .y = a.z * b.x - a.x * b.z,
    .z = a.x * b.y - a.y * b.x
  };
  return result;
}

float vec3_dot(vec3_t a, vec3_t b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

float vec2_dot(vec2_t a, vec2_t b){
	return (a.x*b.x) + (a.y*b.y);
}