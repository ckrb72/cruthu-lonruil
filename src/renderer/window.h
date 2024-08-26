#pragma once
#include <stdbool.h>

typedef struct window_t window_t;

window_t* clCreateWindow(int width, int height, const char* title);
void clDestroyWindow(window_t* window);

bool clWindowShouldClose(window_t* window);

void clSwapBuffers(window_t* window);
