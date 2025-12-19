#ifndef SCENE_H
#define SCENE_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

extern GLfloat w;
extern GLfloat h;
extern double rotate_x;
extern double rotate_y;

void display(void);

#endif