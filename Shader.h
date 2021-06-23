#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
//#include <glad/glad.c>
#include <GLFW/glfw3.h>

using namespace std;

class Shader
{
public:
    // Reference ID of the Shader Program
    GLuint ID;
    // Constructor that build the Shader Program from 2 different shaders
    Shader(const char* vertexPath, const char* fragmentPath);

    // Activates the Shader Program
    void Activate();
    // Deletes the Shader Program
    void Delete();
private:
    // Checks if the different Shaders have compiled properly
    void checkCompileErrors(unsigned int shader, string type);
};
