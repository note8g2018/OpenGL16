#pragma once

#include <iostream>

#include <glad/glad.h>
#include <glad/glad.c>
#include <GLFW/glfw3.h>

#include "Windowing.h"
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

using namespace std;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};
// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

//static float speed_factor = 1.0f;

int main()
{
    // windowing ************************
    int width_window = 1200;
    int height_window = 900;
    string title_window = "OpenGL";
    Windowing windowing = Windowing(width_window, height_window, title_window);
    GLFWwindow* window = windowing.run();

    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("default.vert", "default.frag");

    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO attributes such as coordinates and colors to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*) 0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Texture
    Texture brickTex("brick.png",
        GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    brickTex.texUnit(shaderProgram, "tex0", 0);

    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);

    // Creates camera object
    Camera camera(width_window, height_window, glm::vec3(0.0f, 0.0f, 2.0f));
    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

    // render loop
    // -----------
    while(!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        windowing.processInput();
        // render
        // ------
        glClearColor(0.1f, 0.5f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();
        // Handles camera inputs
        camera.Inputs(window, deltaTime);
        // Updates and exports the camera matrix to the Vertex Shader
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
        // Binds texture so that is appears in rendering
        brickTex.Bind();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int),
            GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, 
        // mouse moved etc.)
        // -------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    brickTex.Delete();
    shaderProgram.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();

    exit(EXIT_SUCCESS);
}

