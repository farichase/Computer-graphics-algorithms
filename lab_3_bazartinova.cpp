#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#define PI 3.1415927
#define SCREEN_WIDTH 1000.0
#define SCREEN_HEIGHT 600.0
using namespace std;
GLFWwindow *window;
GLfloat turnX = 0.0f;
GLfloat turnY = 0.0f;
GLfloat halfW;
GLfloat halfH;
GLfloat radius;
GLfloat height;
GLfloat angle_stepsize;
GLfloat gorizontal_break;
GLfloat base_break;
vector<vector<GLfloat>> vertexesVertical;
vector<vector<vector<GLfloat>>> vertexesBase;
vector<GLfloat> coordinatesZ;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
    const GLfloat turning = 10;
    if (action == GLFW_PRESS || action == GLFW_REPEAT){
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
            radius += 5;
            break;
        case GLFW_KEY_8:
            radius -= 5;
            break;
        case GLFW_KEY_9:
            angle_stepsize += 0.01;
            break;
        case GLFW_KEY_0:
            angle_stepsize -= 0.01;
            break;
        case GLFW_KEY_Q:
            height += 5;
            break;
        case GLFW_KEY_W:
            height -= 5;
            break;
        case GLFW_KEY_G:
            gorizontal_break += 1;
            break;
        case GLFW_KEY_F:
            gorizontal_break -= 1;
            break;
        case GLFW_KEY_M:
            base_break += 1;
            break;
        case GLFW_KEY_V:
            base_break -= 1;
            break;
        }
    }
}
void recalculation(){
    GLfloat x = 0.0, y = 0.0, angle = 0.0;
    vertexesVertical.clear();
    vertexesBase.clear();
    GLfloat step = 0;
    coordinatesZ.clear();
    while (step <= height){
        coordinatesZ.push_back(step);
        if (step == height) break;
        if (gorizontal_break > 0) step += height / gorizontal_break;
    }
    if (step != height) coordinatesZ.push_back(height);
    while (angle < 2 * PI) {   
        x = radius * cos(angle);
        y = radius * sin(angle);
        vector<GLfloat> forXY;
        forXY.push_back(x);
        forXY.push_back(y);
        vertexesVertical.push_back(forXY);
        step = radius / base_break;
        vector<vector<GLfloat>> oneRadius;
        go:
        while (step <= radius){
            x = step * cos(angle);
            y = step * sin(angle);
            forXY.clear();
            forXY.push_back(x);
            forXY.push_back(y);
            oneRadius.push_back(forXY);
            if (step == radius) break;
            if (base_break > 0) step += radius / base_break;
        }
        if (step != radius){
            step = radius;
            goto go;
        }
        vertexesBase.push_back(oneRadius);
        oneRadius.clear();
        angle = angle + angle_stepsize; 
    }
}
void drawCube()
{
    //cube
    GLfloat x1 = SCREEN_WIDTH / 4, y1 = SCREEN_HEIGHT / 4, z1 = -500, a = 50.0;
    GLfloat points[] =
        {
            // top face
            x1 - a, y1 + a, z1 + a, // top left
            x1 - a, y1 + a, z1 - a, // top right
            x1 + a, y1 + a, z1 - a, // bottom right
            x1 + a, y1 + a, z1 + a, // bottom left

            // front face
            x1 - a, y1 + a, z1 + a, // top left
            x1 + a, y1 + a, z1 + a, // top right
            x1 + a, y1 - a, z1 + a, // bottom right
            x1 - a, y1 - a, z1 + a, // bottom left
            // right face
            x1 + a, y1 + a, z1 + a, // top left
            x1 + a, y1 + a, z1 - a, // top right
            x1 + a, y1 - a, z1 - a, // bottom right
            x1 + a, y1 - a, z1 + a, // bottom left
            // back face
            x1 - a, y1 + a, z1 - a, // top left
            x1 + a, y1 + a, z1 - a, // top right
            x1 + a, y1 - a, z1 - a, // bottom right
            x1 - a, y1 - a, z1 - a, // bottom left
            // left face
            x1 - a, y1 + a, z1 + a, // top left
            x1 - a, y1 + a, z1 - a, // top right
            x1 - a, y1 - a, z1 - a, // bottom right
            x1 - a, y1 - a, z1 + a, // bottom left
            // bottom face
            x1 - a, y1 - a, z1 + a, // top left
            x1 - a, y1 - a, z1 - a, // top right
            x1 + a, y1 - a, z1 - a, // bottom right
            x1 + a, y1 - a, z1 + a, // bottom left
        };
    GLfloat color[] = {
        1.f, 1.f, 0.f,
        0.f, 1.f, 1.f,
        0.f, 1.f, 0.f,
        1.f, 0.f, 0.f,
        0.f, 0.f, 1.f,
        1.f, 0.f, 1.f};
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(130.0, 1000.0 / 600.0, 0.1, 1000.0);
    glRotatef(45, 1, 0, 0);
    glRotatef(45, 0, 1, 0);
    glRotatef(20, 1, 0, 0);
    glRotatef(-30, 0, 1, 0);
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_WIDTH, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++)
    {
        glColor3f(color[3 * i], color[3 * i + 1], color[3 * i + 2]);
        for (int j = 0; j < 4; j++)
        {
            glVertex3f(points[i * 12 + 3 * j],
                       points[i * 12 + 3 * j + 1],
                       points[i * 12 + 3 * j + 2]);
        }
    }
    glEnd();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
void drawCylinder()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_COLOR_ARRAY);
    GLfloat x, y, angle;
    int currentColor = 0, index = 0, colorOfThePrevious = 0, recalculationInitalXY = 0;
    recalculation();
    glBegin(GL_QUAD_STRIP); //tube
    GLfloat indexZ = 1;
    while (indexZ < coordinatesZ.size()) { //рисую tube
        angle = 0.0;
        GLfloat lastX = radius, lastY = 0.0;
        index = 0;
        if (colorOfThePrevious != 0) currentColor = -1;
        else currentColor = 0;
        while (index < vertexesVertical.size()){
            x = vertexesVertical[index][0];
            y = vertexesVertical[index][1];
            if (currentColor == 0){
                glColor3f(1.0, 1.0, 0.0);
                --currentColor;
            }
            else {
                glColor3f(1.0, 0.0, 1.0);
                ++currentColor;
            }
            if (recalculationInitalXY == 0) {
                lastX = radius;
                lastY = 0.0;
            }
            else {
                lastX = vertexesVertical[index - 1][0];
                lastY = vertexesVertical[index - 1][1];
            }
            recalculationInitalXY++;
            glVertex3f(lastX, lastY, coordinatesZ[indexZ - 1]); 
            glVertex3f(lastX, lastY, coordinatesZ[indexZ]);
            glVertex3f(x, y, coordinatesZ[indexZ - 1]);
            glVertex3f(x, y, coordinatesZ[indexZ]);
            if (index == 0) colorOfThePrevious = currentColor;
            index++;
        }
        glVertex3f(radius, 0.0, coordinatesZ[indexZ - 1]);
        glVertex3f(radius, 0.0, coordinatesZ[indexZ]);
        if (gorizontal_break > 0) {
            recalculationInitalXY = 0;
        }
        indexZ++;
    }
    glEnd();
    currentColor = 0;
    GLfloat step = 0.0; //top && bottom
    while (step <= height) {
        int index1 = 0, index2, color;
        GLfloat lastX, lastY;
        while (index1 < vertexesBase.size()){
            index2 = 0;
            if (colorOfThePrevious != 0) currentColor = -1;
            else currentColor = 0;
            while(index2 < vertexesBase[0].size()){
                glBegin(GL_POLYGON);
                if (index1 == vertexesBase.size() - 1) {
                    index = 0;
                } else {
                    index = index1 + 1;
                }
                if (currentColor == 0){
                    glColor3f(1.0, 1.0, 0.6);
                    --currentColor;
                }
                else {
                    glColor3f(1.0, 0.6, 1.0);
                    ++currentColor;
                }
                lastX = vertexesBase[index1][index2][0];
                lastY = vertexesBase[index1][index2][1];
                x = vertexesBase[index][index2][0];
                y = vertexesBase[index][index2][1];
                if (index2 == 0){
                    glVertex3f(0, 0, step);
                    glVertex3f(lastX, lastY, step);
                    glVertex3f(x, y, step);
                    glVertex3f(0, 0, step);                 
                } else {
                    glVertex3f(vertexesBase[index1][index2 - 1][0], vertexesBase[index1][index2 - 1][1], step);
                    glVertex3f(vertexesBase[index][index2 - 1][0], vertexesBase[index][index2 - 1][1], step);
                    glVertex3f(x, y, step);
                    glVertex3f(lastX, lastY, step);
                }
                if (index2 == 0) colorOfThePrevious = currentColor;
                index2++;
                glEnd();
            }
            index1++; 
        }
        step += height; 
    }

    drawCube();
}
int main()
{
    if (!glfwInit())
    {
        return -1;
    }
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "drawing", NULL, NULL);
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
    gluPerspective(130.0, 1000.0 / 600.0, 0.1, 1000.0);
    glRotatef(45, 1, 0, 0);
    glRotatef(45, 0, 1, 0);
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_WIDTH, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    halfW = SCREEN_WIDTH / 2 + 100;
    halfH = SCREEN_HEIGHT / 2 - 100;
    angle_stepsize = 0.1;
    radius = 100;
    height = 250;
    gorizontal_break = 1.0;
    base_break = 2.0;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glTranslatef(halfW, halfH, -500.0);
        glRotatef(turnX, 1, 0, 0);
        glRotatef(turnY, 0, 1, 0);
        drawCylinder();
        glPopMatrix();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
