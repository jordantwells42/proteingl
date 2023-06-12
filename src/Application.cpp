#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"IBO.h"
#include"Camera.h"

int width = 800;
int height = 800;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

   
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error" << std::endl;
    

    std::cout << glGetString(GL_VERSION) << std::endl;


    float positions[] = {
        0.0f,0.0f,0.0f,
        0.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f,
        0.0f,1.0f,1.0f,
        1.0f,0.0f,0.0f,
        1.0f,0.0f,1.0f,
        1.0f,1.0f,0.0f,
        1.0f,1.0f,1.0f,
    };

    unsigned int indices[] = {
        0,2,3,
        0,3,1,
        1,3,7,
        1,7,5,
        4,6,2,
        4,2,0,
        5,7,6,
        5,6,4,
        0,4,5,
        0,5,1,
        2,6,7,
        2,7,3
    };

    Shader shaderProgram("./res/shaders/vert_basic.shader", "./res/shaders/frag_basic.shader");
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(positions, sizeof(positions));
    IBO IBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);
    //VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    IBO1.Unbind();

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);

    unsigned int camPosLoc = glGetUniformLocation(shaderProgram.ID, "camPos");

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.5, 0.5, 0.5, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();
        VAO1.Bind();

        double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1 / 60) {
            rotation += 0.05f;
            prevTime = crntTime;
        }

        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
        glUniform3fv(camPosLoc, 1, &camera.Position[0]);


        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    VBO1.Delete();
    IBO1.Delete();
    VAO1.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}