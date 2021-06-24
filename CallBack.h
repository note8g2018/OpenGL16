#pragma once

#include <glad/gl.h>
//#include <glad/glad.c>
#include <GLFW/glfw3.h>

#include "Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width_window,
    int height_window);

void key_callback(GLFWwindow* window, int key, int scancode,
    int action, int mods);


