#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

GLFWwindow *window;
GLfloat turnX = 0.0f;
GLfloat turnY = 0.0f;
GLfloat halfW;
GLfloat halfH;
GLfloat rib;
GLfloat perspective[] = {
        1.0, 0.0, 0.0, 1.0 / 2.0,
        0.0, 1.0, 0.0, 1.0 / 2.0,
        0.0, 0.0, 1.0, 1.0 / 2.0,
        0.0, 0.0, 0.0, 1.0 
    };
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    const GLfloat turning = 10;
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            turnX -= turning;
            break;
        case GLFW_KEY_DOWN:
            turnX += turning;
            break;
        case GLFW_KEY_RIGHT:
            turnY += turning;
            break;
        case GLFW_KEY_LEFT:
            turnY -= turning;
            break;
        case GLFW_KEY_1:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case GLFW_KEY_2:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        case GLFW_KEY_3:
            halfW += 2;
            break;
        case GLFW_KEY_4:
            halfH -= 2;
            break;
        case GLFW_KEY_5:
            halfW -= 2;
            break;
        case GLFW_KEY_6:
            halfH += 2;
            break;
        case GLFW_KEY_7:
            rib += 2;
            break;
        case GLFW_KEY_8:
            rib -= 2;
            break;
        }
    }
}
void draw(GLfloat x, GLfloat y, GLfloat z, GLfloat ribLength)
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat a = ribLength;
    GLfloat points[] =
        {
            // top face
            x - a, y + a, z + a, // top left
            x - a, y + a, z - a, // top right
            x + a, y + a, z - a, // bottom right
            x + a, y + a, z + a, // bottom left
            
            // front face
            x - a, y + a, z + a, // top left
            x + a, y + a, z + a, // top right
            x + a, y - a, z + a, // bottom right
            x - a, y - a, z + a, // bottom left
            // right face
            x + a, y + a, z + a, // top left
            x + a, y + a, z - a, // top right
            x + a, y - a, z - a, // bottom right
            x + a, y - a, z + a , // bottom left
            // back face
            x - a, y + a, z - a, // top left
            x + a, y + a, z - a, // top right
            x + a, y - a, z - a, // bottom right
            x - a, y - a, z - a, // bottom left
            // left face
            x - a, y + a, z + a, // top left
            x - a, y + a, z - a, // top right
            x - a, y - a, z - a, // bottom right
            x - a, y - a, z + a, // bottom left
            // bottom face
            x - a, y - a, z + a, // top left
            x - a, y - a, z - a, // top right
            x + a, y - a, z - a, // bottom right
            x + a, y - a, z + a, // bottom left
            
        };
    GLfloat color[] = {
        1.f, 1.f, 0.f,
        0.f, 1.f, 1.f,
        0.f, 1.f, 0.f,
        1.f, 0.f, 0.f,
        0.f, 0.f, 1.f,
        1.f, 0.f, 1.f
    };
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_COLOR_ARRAY);  
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++)
    {
        glColor3f(color[3 * i], color[3 * i + 1], color[3 * i + 2]);
        for (int j = 0; j < 4; j++)
        {
            glVertex3f(points[i * 12 + 3 * j], points[i * 12 + 3 * j + 1], points[i * 12 + 3 * j + 2]);
        }
    }
    glEnd();
    x = SCREEN_WIDTH / 2 , y = SCREEN_HEIGHT / 2 - 30, z = -500, a = 70.0;
    GLfloat points2[] = {
        // top face
            x - a, y + a, z + a, // top left
            x - a, y + a, z - a, // top right
            x + a, y + a, z - a, // bottom right
            x + a, y + a, z + a, // bottom left 
            // front face
            x - a, y + a, z + a, // top left
            x + a, y + a, z + a, // top right
            x + a, y - a, z + a, // bottom right
            x - a, y - a, z + a, // bottom left
            // right face
            x + a, y + a, z + a, // top left
            x + a, y + a, z - a, // top right
            x + a, y - a, z - a, // bottom right
            x + a, y - a, z + a , // bottom left
    };
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glLoadMatrixf(perspective);             
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_WIDTH, 0, 1000); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(20, 1, 0, 0);
    glRotatef(-30, 0, 1, 0);
    glBegin(GL_QUADS);
    for (int i = 0; i < 3; i++)
    {
        glColor3f(color[3 * i], color[3 * i + 1], color[3 * i + 2]);
        for (int j = 0; j < 4; j++)
        {
            glVertex3f(points2[i * 12 + 3 * j], points2[i * 12 + 3 * j + 1], points2[i * 12 + 3 * j + 2]);
        }
    }
    glEnd();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_CULL_FACE);
    glDisableClientState(GL_COLOR_ARRAY);
}
int main()
{
    if ( !glfwInit( ) )
    {
        return -1;
    }
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cube", NULL, NULL);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glViewport(0.0f, 0.0f, screenWidth, screenWidth);   
    glMatrixMode(GL_PROJECTION);                         
    glLoadIdentity();
    glLoadMatrixf(perspective);        
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_WIDTH, 0, 1000); 
    glMatrixMode(GL_MODELVIEW);                          
    glLoadIdentity();                               
    halfW = SCREEN_WIDTH / 2;
    halfH = SCREEN_HEIGHT / 2 + 25;
    rib = 100;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glTranslatef(halfW, halfH, -500);
        glRotatef(turnX, 1, 0, 0);
        glRotatef(turnY, 0, 1, 0);
        glTranslatef(-halfW, -halfH, 500);
        draw(halfW, halfH, -500, rib);
        glPopMatrix();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
