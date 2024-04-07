#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
// #include "SDL_mixer.h"
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"
#include "mesh.h"

//color codes:
  //#F9DCE8 - soft pink
  //#FEBFDF - darker pink
  //#3A405A - muted navy

// to run the program
// gcc -Wall -g -std=c99 -I/opt/homebrew/opt/sdl2/include -L/opt/homebrew/opt/sdl2/lib ./src/*.c -o main -lSDL2
// ./main

//SDL_GET_TICKS
//1000ms = 1second

SDL_Window *window;
SDL_Renderer *renderer;

SDL_Texture *texture;
bool is_running = false;
uint32_t *color_buffer = NULL; // color buffer
int window_width = 1280;
int window_height = 720;

bool initialize_windowing_system();
void process_keyboard_input();
void run_render_pipeline();
void set_up_memory_buffers();
void clear_color_buffer(uint32_t);
void draw_Dots();
void draw_Grid();
void draw_Rect(int, int, int, int, uint32_t);
void project_model(void);

// Cube Rotation and Creation
#define N_CUBE_POINTS 9 * 9 * 9
vec3_t camera_position = {0, 0, 0};
vec3_t cube_model[N_CUBE_POINTS];
vec2_t projected_points[N_CUBE_POINTS];
float rotation_angle = 0.0;
vec3_t cube_rotation = {.x = 0, .y = 0, .z = 0};
void draw_Pixels(int x, int y, uint32_t color);

void translate_cube(int tranX, int tranY, float scaling_factor);
void draw_cube(int tranX, int tranY, float scaling_factor);

// Clear up memory after
void clean_up_windowing_system();
void update_state();

// New Cube Mesh Code
triangle_t triangles_to_render[1000];
void draw_Line(int x1, int y1, int x2, int y2, uint32_t color);
void draw_Triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color);
int t_count = 0;
//int Square_count = 0;
//void test_update();

// Mix_Music* gMusic = NULL;

//vec3_t transformed_vertex;

int main(void)
{
  is_running = initialize_windowing_system();
  set_up_memory_buffers();

  // FullScreen//
  // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
  // build_cube_model();

  while (is_running)
  {
    //Testing concurrent animation. Current Flaw: How to make it concurrent
    process_keyboard_input();
    // Mix_PlayMusic(gMusic, -1);
    update_state();
    run_render_pipeline();
    SDL_Delay(16);
  }
  clean_up_windowing_system();
  free(color_buffer);

  return 0;
}

// void test_update(){
//   draw_Rect(0,10,50,50, 0xFFFFFFFF);
// }

bool initialize_windowing_system()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return false;
  }
  window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_ALLOW_HIGHDPI);
  if (!window)
  {
    fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    // SDL_Quit();
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer)
  {
    fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
    // SDL_DestroyWindow(window);
    // SDL_Quit();
    return false;
  }

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
  if (!texture)
  {
    fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
    return false;
  }

  // if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  // {
  //   printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
  //   success = false;
  // }
  
  // gMusic = Mix_LoadMUS("song.wav");
  // if (gMusic == NULL)
  // {
  //   printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
  //   success = false;
  // }

  return true;
}

void process_keyboard_input()
{
  SDL_Event event;
  SDL_PollEvent(&event); // filling &event with data

  switch (event.type)
  {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE)
    {
      is_running = false;
    }
    break;
  }
}

void update_state()
{
  clear_color_buffer(0xFF3A405A);
  // rotation_angle += 0.005;
  cube_rotation.x += 0.01;
  cube_rotation.y += 0.01;
  cube_rotation.z += 0.01;

  project_model();

  draw_cube(0,0,2);



  //testing time.
  // if(Square_count < 300){
  //     draw_Rect(0+Square_count,10,50,50, 0xFFFFFFFF);
  //     Square_count++;
  //   }
}

void clean_up_windowing_system()
{
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  // Mix_FreeMusic(gMusic);
  // gMusic = NULL;
  // Mix_Quit();
  SDL_Quit();
}

void run_render_pipeline()
{
  // SDL_SetRenderDrawColor(renderer, 230, 230, 250, 255); //lavender color
  // SDL_RenderClear(renderer);

  // SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

  SDL_UpdateTexture(texture, NULL, color_buffer, window_width * sizeof(uint32_t)); // updates the whole texture by calling the color buffer
  SDL_RenderCopy(renderer, texture, NULL, NULL);

  SDL_RenderPresent(renderer);
}

void set_up_memory_buffers()
{
  color_buffer = (uint32_t *)malloc(window_width * window_height * sizeof(uint32_t));
}

void clear_color_buffer(uint32_t color)
{ // clear is another way to say paint
  // for loop paint brush
  for (int i = 0; i < window_width * window_height; ++i)
  {
    color_buffer[i] = color;
  }
}

void draw_Grid()
{
  // horizontal
  for (int y = 0; y < window_height; y += 40)
  {
    for (int x = 0; x < window_width; ++x)
    {
      color_buffer[y * window_width + x] = 0xFF000000;
    }
  }

  // vertical
  for (int x = 0; x < window_width; x += 40)
  {
    for (int y = 0; y < window_height; ++y)
    {
      color_buffer[y * window_width + x] = 0xFF000000;
    }
  }
}

// Draws a rectangle at a specified position with a specified color.
void draw_Rect(int x, int y, int width, int height, uint32_t color)
{
  for (int i = x; i < x + width; ++i)
  {
    for (int j = y; j < y + height; ++j)
    {
      color_buffer[j * window_width + i] = color;
    }
  }
}

void draw_Triangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color)
{
  draw_Line(x1, y1, x2, y2, color);
  draw_Line(x2, y2, x3, y3, color);
  draw_Line(x3, y3, x1, y1, color);
}

void draw_Line(int x1, int y1, int x2, int y2, uint32_t color)
{
  int deltaX = x2 - x1;
  int deltaY = y2 - y1;

  int steps = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

  float x_inc = deltaX / (float)steps;
  float y_inc = deltaY / (float)steps;

  float x = x1;
  float y = y1;

  for (int i = 0; i <= steps; i++)
  {
    draw_Pixels((int)x, (int)y, color);
    x += x_inc;
    y += y_inc;
  }
}

void draw_Pixels(int x, int y, uint32_t color)
{
  if (x < window_width && y < window_height)
  {
    color_buffer[(y * window_width) + x] = color;
  }
}
// Draws dots at regular intervals by setting pixels in the color buffer.
void draw_Dots()
{
  for (int x = 0; x < window_width; x += 20)
  {
    for (int y = 0; y < window_height; y += 20)
    {
      color_buffer[y * window_width + x] = 0xFF000000;
    }
  }
}

// Projects a 3D point to a 2D point in an orthographic projection.
vec2_t orthographic_project_point(vec3_t point_3d)
{
  vec2_t projected_point = {.x = point_3d.x, .y = point_3d.y};
  return projected_point;
}

vec2_t perspective_project_point(vec3_t point_3d)
{
  point_3d.x -= camera_position.x;
  point_3d.y -= camera_position.y;
  point_3d.z -= camera_position.z;

  // float perspective_factor = 1.0 / (1.0 + point_3d.z);

  int scaling_factor = 100;

  vec2_t projected_point = {point_3d.x / point_3d.z, point_3d.y / point_3d.z};
  projected_point.x *= scaling_factor;
  projected_point.y *= scaling_factor;
  return projected_point;

}

// Projects all 3D points in the cube_model to 2D points using orthographic projection.
void project_model()
{
  for (int i = 0; i < N_MESH_FACES; i++)
  {
    face_t mesh_face = mesh_faces[i];
    vec3_t face_vertices[3];

    face_vertices[0] = mesh_vertices[mesh_face.a - 1];
    face_vertices[1] = mesh_vertices[mesh_face.b - 1];
    face_vertices[2] = mesh_vertices[mesh_face.c - 1];

    vec3_t transformed_vertices[3];

    for (int j = 0; j < 3; j++)
    {
      vec3_t transformed_vertex = face_vertices[j];

      transformed_vertex = vec3_rotate_x(transformed_vertex, cube_rotation.x);
      transformed_vertex = vec3_rotate_y(transformed_vertex, cube_rotation.y);
      transformed_vertex = vec3_rotate_z(transformed_vertex, cube_rotation.z);

      transformed_vertex.z += 5;
      transformed_vertices[j] = transformed_vertex;
    }

    //back face culling
    vec3_t vertex_a = transformed_vertices[0];
    vec3_t vertex_b = transformed_vertices[1];
    vec3_t vertex_c = transformed_vertices[2];

    //vector subtraction
    vec3_t vector_ab = vec3_subtract(vertex_b, vertex_a);
    vec3_t vector_ac = vec3_subtract(vertex_c, vertex_a);

    //normal using the cross product
    vec3_t normal = vec3_cross(vector_ab, vector_ac);

    vec3_t camera_ray = vec3_subtract(camera_position, vertex_a);

    float dot_normal_camera = vec3_dot(camera_ray, normal);

    if(dot_normal_camera < 0){
      continue;
    }

    triangle_t proj_Triangle;
    for( int j = 0; j <3; j++){
      vec2_t projected_point = perspective_project_point(transformed_vertices[j]);

      // projected_point.x += (window_width /2);
      // projected_point.y += (window_height /2);

      proj_Triangle.points[j] = projected_point;
    }
    triangles_to_render[t_count++] = proj_Triangle;
  }
}

//this function draws the cube with an added option for translation
void draw_cube(int tranX, int tranY, float scaling_factor){ // default: 0, 0, 1
  translate_cube(tranX, tranY, scaling_factor);
  //scale_cube(scaling_factor);
}

void translate_cube(int tranX, int tranY, float scaling_factor){
  for (int i = 0; i < t_count; i++)
  {
    triangle_t render_tri = triangles_to_render[i];
    for (int j = 0; j < 3; j++)
    {
      
      draw_Rect((render_tri.points[0].x + (window_width/2) + tranX), (render_tri.points[0].y + (window_height/2) + tranY), 4, 4, 0xFFFEBFDF);
      draw_Rect((render_tri.points[1].x + (window_width/2) + tranX), (render_tri.points[1].y + (window_height/2) + tranY), 4, 4, 0xFFFEBFDF);
      draw_Rect((render_tri.points[2].x + (window_width/2) + tranX), (render_tri.points[2].y + (window_height/2) + tranY), 4, 4, 0xFFFEBFDF);

      draw_Triangle(
      (render_tri.points[0].x)*scaling_factor + (window_width/2) + tranX, (render_tri.points[0].y)*scaling_factor + (window_height/2) + tranY, 
      (render_tri.points[1].x)*scaling_factor + (window_width/2) + tranX, (render_tri.points[1].y)*scaling_factor + (window_height/2) + tranY, 
      (render_tri.points[2].x)*scaling_factor + (window_width/2) + tranX, (render_tri.points[2].y)*scaling_factor + (window_height/2) + tranY, 0xFFF9DCE8);
    }

  }

  t_count = 0;
}