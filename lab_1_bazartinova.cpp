#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

float color[3];

void error(int error, const char *description)
{
    fputs(description, stderr);
}

void show(GLFWwindow *window)
{
    int a, b; 
    glfwGetFramebufferSize(window, &a, &b);
    float r = a / (float)b;
    glViewport(0, 0, a, b);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(-r, r, -1.f, 1.f, 1.f, -1.f);
    glBegin(GL_TRIANGLES);
    glColor3f(color[0], color[1], color[2]);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();
}

void key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
    {   
        float t = color[0];
        color[0] = color[1];
        color[1] = color[2];
        color[2] = t;
        show(window);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        glfwMaximizeWindow(window);
    }
}

void mKey(GLFWwindow *window, int button, int scancode, int action)
{    
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
    glfwSetErrorCallback(error);

    if (!glfwInit())
        exit(1);

    GLFWwindow *window = glfwCreateWindow(640, 640, "TRIANGLE", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key);
    glfwSetMouseButtonCallback(window, mKey);
 
    color[1] = color[2] = 1.f;
    color[0] = 0.f;
    while (!glfwWindowShouldClose(window))
    {
        show(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}