#pragma once

#include <iostream>

#include <glad/gl.h>
//#include <glad/glad.c>
#include <GLFW/glfw3.h>

#include "CallBack.h"

using namespace std;

class Windowing
{
	
public:
	GLFWwindow* window;
	int& width_window;
	int& height_window;
	string& title_window;

	Windowing(int& width_window, int& height_window, string& title_window);
	~Windowing();

	void set_callBack_functions();
	GLFWwindow* run();
	void processInput();

private:

};




