#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <fstream>
#include <SOIL/SOIL.h>
#define GL_LIGHT3 0x4003
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
GLboolean IS_TEXTURE = false;
GLboolean light = false;
GLboolean ambient = true;
GLboolean diffuse = true;
GLboolean specular = true;
GLboolean anim = false;
GLboolean flag = false;
float FPS = 0;
float FPS_time = 0;
int l;
vector<vector<GLfloat>> vertexesVertical;
vector<vector<vector<GLfloat>>> vertexesBase;
vector<GLfloat> coordinatesZ;
GLfloat lightColor[] = {0.2, 0.2, 0.2, 1.0};
GLfloat ambientM[] = {0.14, 0.4, 0.4, 1.0};
GLfloat diffuseM[] = {0.6, 0.2, 0.36, 1.0};
GLfloat specularM[] = {0.0, 0.24, 0.0, 1.0};
GLfloat ambientL[] = {0.67, 0.2, 0.15, 1.0};
GLfloat diffuseL[] = {0.1, 0.34, 0.3, 1.0};
GLfloat specularL[] = {0.2, 0.4, 0.2, 1.0};
GLfloat t;
void load() {
    ifstream file("save.txt");
    file >> turnX >> turnY >> halfH >> halfW >> radius >>
    angle_stepsize >> height >> gorizontal_break >> base_break >>
    IS_TEXTURE >> light >> anim;
    file.clear();
    file.close();
}
void save(){
    ofstream fout;
    fout.open("save.txt");
    if (fout.is_open()) {
        cout << "yes" << endl;
        fout << turnX << endl << turnY << endl << halfH << endl <<
                halfW << endl << radius << endl << angle_stepsize <<
                endl << height << endl << gorizontal_break << endl <<
                base_break << endl << IS_TEXTURE << endl << light <<
                endl << anim << endl;
    }
    fout.close();
}
void lightChange(string name, bool sign){
    if (name == "GL_AMBIENT"){
        if (sign) {
            ambientM[0] += 0.05;
            ambientM[1] += 0.05;
            ambientM[2] += 0.05;
        } else {
            ambientM[0] -= 0.05;
            ambientM[1] -= 0.05;
            ambientM[2] -= 0.05;
        }
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambientM);
    }
    if (name == "GL_DIFFUSE"){
        if (sign) {
            diffuseM[0] += 0.05;
            diffuseM[1] += 0.05;
            diffuseM[2] += 0.05;
        } else {
            diffuseM[0] -= 0.05;
            diffuseM[1] -= 0.05;
            diffuseM[2] -= 0.05;
        }
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseM);
    }
    if (name =="GL_SPECULAR"){
        if (sign) {
            specularM[0] += 0.05;
            specularM[1] += 0.05;
            specularM[2] += 0.05;
        } else {
            specularM[0] -= 0.05;
            specularM[1] -= 0.05;
            specularM[2] -= 0.05;
        }
        glMaterialfv(GL_FRONT, GL_SPECULAR, specularM);
    }
}
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
            angle_stepsize += 2;
            break;
        case GLFW_KEY_0:
            if (angle_stepsize > 2) angle_stepsize -= 2;
            break;
        case GLFW_KEY_Q:
            height += 5;
            break;
        case GLFW_KEY_W:
            height -= 5;
            break;
        case GLFW_KEY_E:
            gorizontal_break += 1;
            break;
        case GLFW_KEY_R:
            gorizontal_break -= 1;
            break;
        case GLFW_KEY_U:
            base_break += 1;
            break;
        case GLFW_KEY_Y:
            base_break -= 1;
            break;
        case GLFW_KEY_T:
            IS_TEXTURE = !IS_TEXTURE;
            break;
        case GLFW_KEY_A:
            lightChange("GL_AMBIENT", false);
            break;
        case GLFW_KEY_S:
            lightChange("GL_AMBIENT", true);
            break;
        case GLFW_KEY_D:
            lightChange("GL_SPECULAR", false);
            break;
        case GLFW_KEY_F:
            lightChange("GL_SPECULAR", true);
            break;
        case GLFW_KEY_G:
            lightChange("GL_DIFFUSE", false);
            break;
        case GLFW_KEY_H:
            lightChange("GL_DIFFUSE", true);
            break;
        case GLFW_KEY_L:
            light = !light;
            break;
        case GLFW_KEY_ENTER:
            anim = !anim;
            t = 0;
            break;
        case GLFW_KEY_M:
            save();
            break;
        case GLFW_KEY_N:
            load();
            break;
        }
    }
}

GLuint texture;
void light_on(){
    GLfloat position[] = {1.5, -1.2, 15.0, 1.0};
    if(light)
        glEnable(GL_LIGHTING);
    else
        glDisable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    GLfloat nul = {0.0};
    GLfloat hundr = {100.0};
    GLfloat nulArr[] = {0.0, 0.0, 0.0, 0.0};
    glLightfv(GL_LIGHT0,GL_SPOT_EXPONENT, &nul);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    if (ambient) {
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientL);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambientM);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightColor);
    } else {
        glLightfv(GL_LIGHT0, GL_AMBIENT, nulArr);
        glMaterialfv(GL_FRONT, GL_AMBIENT, nulArr);
    }        

    if (specular) {     
        glLightfv(GL_LIGHT0, GL_SPECULAR, specularL);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specularM);
        glMaterialfv(GL_FRONT, GL_SHININESS, &hundr);
    }
    else {
        glLightfv(GL_LIGHT0, GL_SPECULAR, nulArr);
        glMaterialfv(GL_FRONT, GL_SPECULAR, nulArr);
        glMaterialfv(GL_FRONT, GL_SHININESS, &nul);
    }

    if (diffuse) {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseL);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseM);
    } else {
        glLightfv(GL_LIGHT0, GL_DIFFUSE, nulArr);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, nulArr);
    }    
}

void loadTexture() {
    int w  , h;
    unsigned char* img = SOIL_load_image("pic.jpg" , &w , &h ,  0 , SOIL_LOAD_RGBA);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    SOIL_free_image_data(img);
    glBindTexture(GL_TEXTURE_2D, 0);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
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
    while (angle <= 2 * PI) { 
        ang:  
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
        if (angle_stepsize > 0) angle = angle + 2*PI / angle_stepsize; 
    }
    if (vertexesVertical[0][0] != vertexesVertical[vertexesVertical.size()-1][0]){
        vector<GLfloat> forXY;
        forXY.push_back(vertexesVertical[0][0]);
        forXY.push_back(vertexesVertical[0][1]);
        vertexesVertical.push_back(forXY);
    }
}
GLboolean k = true;
GLfloat calcul(GLfloat a, GLfloat b){
    return pow(1-t, 3)*a+3*t*pow(1-t, 2)*(-100) + 3*pow(t, 2)*(1-t)*(260) + pow(t, 3)*b;
}
void drawWithAnim() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_COLOR_ARRAY);
    GLfloat x, y, angle;
    int currentColor = 0, index = 0, colorOfThePrevious = 0, recalculationInitalXY = 0;
    recalculation();      
    GLfloat indexZ = 1;
    GLfloat bx, by, bz;
    glNewList(l, GL_COMPILE);
    while (indexZ < coordinatesZ.size()) { //рисую tube
        angle = 0.0;
        GLfloat lastX = radius, lastY = 0.0;
        index = 1;
        while (index < vertexesVertical.size()){
            x = vertexesVertical[index][0];
            y = vertexesVertical[index][1];
            if (IS_TEXTURE) glColor3f(1.0, 1.0, 1.0);
            else{
                if (currentColor == 0){
                    glColor3f(1.0, 1.0, 0.0);
                    --currentColor;
                    if (index == vertexesVertical.size() - 1) ++currentColor;
                }
                else {
                    glColor3f(1.0, 0.0, 1.0);
                    ++currentColor;
                    if (index == vertexesVertical.size() - 1) --currentColor;
                }
            }
            lastX = vertexesVertical[index - 1][0];
            lastY = vertexesVertical[index - 1][1];
            glBegin(GL_QUAD_STRIP);
            //glBegin(GL_QUADS);
            bx = calcul(lastX, lastX);
            by = calcul(lastY, lastY);
            bz = calcul(coordinatesZ[indexZ - 1], -coordinatesZ[indexZ - 1]);
            if (IS_TEXTURE) glTexCoord2f(lastX / radius, coordinatesZ[indexZ - 1] / height);
            if (light) glNormal3f(-lastX, lastY, 0);
            glVertex3f(bx, by, bz);  
            bx = calcul(x, x);
            by = calcul(y, y);
            bz = calcul(coordinatesZ[indexZ - 1], -coordinatesZ[indexZ - 1]);
            if (IS_TEXTURE) glTexCoord2f(x / radius, coordinatesZ[indexZ - 1] / height);
            if (light) glNormal3f(-x, -y, 0);
            glVertex3f(bx, by, bz);
            bx = calcul(x, x);
            by = calcul(y, y);
            bz = calcul(coordinatesZ[indexZ], -coordinatesZ[indexZ]);
            if (IS_TEXTURE) glTexCoord2f(x / radius, coordinatesZ[indexZ] / height);
            if (light) glNormal3f(-x, y, 0);
            glVertex3f(bx, by, bz);
            bx = calcul(lastX, lastX);
            by = calcul(lastY, lastY);
            bz = calcul(coordinatesZ[indexZ], -coordinatesZ[indexZ]);
            if (IS_TEXTURE) glTexCoord2f(lastX / radius, coordinatesZ[indexZ] / height);
            if (light) glNormal3f(-lastX, -lastY, 0);
            glVertex3f(bx, by, bz);

            glEnd();
            index++;
        }
        indexZ++;
    }    
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
                if (index1 == vertexesBase.size() - 1) index = 0; 
                else index = index1 + 1;
                if (IS_TEXTURE) glColor3f(1.0, 1.0, 1.0);
                else {
                    if (currentColor == 0){
                        if (step == 0) glColor3f(1.0, 1.0, 0.6);
                        else glColor3f(1.0, 0.6, 1.0);
                        --currentColor;
                    }
                    else {
                        glColor3f(1.0, 1.0, 1.0);
                        ++currentColor;
                    }
                }
                lastX = vertexesBase[index1][index2][0];
                lastY = vertexesBase[index1][index2][1];
                x = vertexesBase[index][index2][0];
                y = vertexesBase[index][index2][1];
                if (!IS_TEXTURE){
                    if (index2 == 0){
                        glBegin(GL_TRIANGLE_STRIP);
                        //glBegin(GL_TRIANGLES);
                        bx = calcul(0, 0);
                        by = calcul(0, 0);
                        bz = calcul(step, -step);
                        glVertex3f(bx, by, bz);
                        bx = calcul(lastX, lastX);
                        by = calcul(lastY, lastY);
                        bz = calcul(step, -step);
                        glVertex3f(bx, by, bz);
                        bx = calcul(x, x);
                        by = calcul(y, y);
                        bz = calcul(step, -step);
                        glVertex3f(bx, by, bz);
                        glEnd();             
                    } else {
                        glBegin(GL_POLYGON);
                        bx = calcul(vertexesBase[index1][index2 - 1][0], vertexesBase[index1][index2 - 1][0]);
                        by = calcul(vertexesBase[index1][index2 - 1][1], vertexesBase[index1][index2 - 1][1]);
                        bz = calcul(step, -step);
                        glVertex3f(bx, by, bz);
                        bx = calcul(vertexesBase[index][index2 - 1][0], vertexesBase[index][index2 - 1][0]);
                        by = calcul(vertexesBase[index][index2 - 1][1], vertexesBase[index][index2 - 1][1]);
                        bz = calcul(step, -step);
                        glVertex3f(bx, by, bz);
                        bx = calcul(x, x);
                        by = calcul(y, y);
                        bz = calcul(step, -step);
                        glVertex3f(bx, by, bz);
                        bx = calcul(lastX, lastX);
                        by = calcul(lastY, lastY);
                        bz = calcul(step, -step);
                        glVertex3f(bx, by, bz);
                        glEnd();
                    }
                } else {
                    glBegin(GL_TRIANGLE_STRIP);
                    //glBegin(GL_TRIANGLES);
                    if (IS_TEXTURE) glTexCoord2d(0, 0);
                    bx = calcul(0, 0);
                    by = calcul(0, 0);
                    bz = calcul(step, -step);
                    glVertex3f(bx, by, bz);
                    if (IS_TEXTURE) glTexCoord2d(lastX / radius, lastY / radius); 
                    bx = calcul(lastX, lastX);
                    by = calcul(lastY, lastY);
                    bz = calcul(step, -step);
                    glVertex3f(bx, by, bz);
                    if (IS_TEXTURE) glTexCoord2d(x / radius, y / radius); 
                    bx = calcul(x, x);
                    by = calcul(y, y);
                    bz = calcul(step, -step);
                    glVertex3f(bx, by, bz);
                    glEnd();
                }
                if (index2 == 0) colorOfThePrevious = currentColor;
                index2++;
                glEnd();
            }
            index1++; 
        }
        step += height; 
    }
    glColor3f(1.0, 1.0, 1.0);
    glEndList();
}
void drawCylinder() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_COLOR_ARRAY);
    glNewList(l, GL_COMPILE);
    GLfloat x, y, angle;
    int currentColor = 0, index = 0, colorOfThePrevious = 0;
    recalculation();      
    GLfloat indexZ = 1;
    glBegin(GL_QUAD_STRIP);
    //glBegin(GL_QUADS);
    while (indexZ < coordinatesZ.size()) { //рисую tube
        angle = 0.0;
        GLfloat lastX = radius, lastY = 0.0;
        index = 1;
        while (index < vertexesVertical.size()){
            x = vertexesVertical[index][0];
            y = vertexesVertical[index][1];
            
            if (IS_TEXTURE) glColor3f(1.0, 1.0, 1.0);
            else{
                if (currentColor == 0){
                    glColor3f(1.0, 1.0, 0.0);
                    --currentColor;
                    if (index == vertexesVertical.size() - 1) ++currentColor;
                }
                else {
                    glColor3f(1.0, 0.0, 1.0);
                    ++currentColor;
                    if (index == vertexesVertical.size() - 1) --currentColor;
                }
            }
            lastX = vertexesVertical[index - 1][0];
            lastY = vertexesVertical[index - 1][1];
            
            if (IS_TEXTURE) glTexCoord2f(lastX / radius, coordinatesZ[indexZ - 1] / height);
            if (light) glNormal3f(-lastX, -lastY, 0);
            glVertex3f(lastX, lastY, coordinatesZ[indexZ - 1]);

            if (IS_TEXTURE) glTexCoord2f(x / radius, coordinatesZ[indexZ - 1] / height);
            if (light) glNormal3f(-x, -y, 0);
            glVertex3f(x, y, coordinatesZ[indexZ - 1]);

            if (IS_TEXTURE) glTexCoord2f(x / radius, coordinatesZ[indexZ] / height);
            if (light) glNormal3f(-x, -y, 0);
            glVertex3f(x, y, coordinatesZ[indexZ]);

            if (IS_TEXTURE) glTexCoord2f(lastX / radius, coordinatesZ[indexZ] / height);
            if (light) glNormal3f(-lastX, -lastY, 0);
            glVertex3f(lastX, lastY, coordinatesZ[indexZ]);
            index++;
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
                if (index1 == vertexesBase.size() - 1) index = 0; 
                else index = index1 + 1;
                if (IS_TEXTURE) glColor3f(1.0, 1.0, 1.0);
                else {
                    if (currentColor == 0){
                        if (step == 0) glColor3f(1.0, 1.0, 0.6);
                        else glColor3f(1.0, 0.6, 1.0);
                        --currentColor;
                    }
                    else {
                        glColor3f(1.0, 1.0, 1.0);
                        ++currentColor;
                    }
                }
                lastX = vertexesBase[index1][index2][0];
                lastY = vertexesBase[index1][index2][1];
                x = vertexesBase[index][index2][0];
                y = vertexesBase[index][index2][1];
                if (!IS_TEXTURE){
                    if (index2 == 0){
                        glBegin(GL_TRIANGLE_STRIP);
                        //glBegin(GL_TRIANGLES);
                        glVertex3f(0, 0, step);
                        glVertex3f(lastX, lastY, step);
                        glVertex3f(x, y, step);
                        glEnd();             
                    } else {
                        glBegin(GL_POLYGON);
                        glVertex3f(vertexesBase[index1][index2 - 1][0], vertexesBase[index1][index2 - 1][1], step);
                        glVertex3f(vertexesBase[index][index2 - 1][0], vertexesBase[index][index2 - 1][1], step);
                        glVertex3f(x, y, step);
                        glVertex3f(lastX, lastY, step);
                        glEnd();
                    }
                } else {
                    glBegin(GL_TRIANGLE_STRIP);
                    //glBegin(GL_TRIANGLES);
                    if (IS_TEXTURE) glTexCoord2d(0, 0);
                    glVertex3f(0, 0, step);
                    if (IS_TEXTURE) glTexCoord2d(lastX / radius, lastY / radius); 
                    glVertex3f(lastX, lastY, step);
                    if (IS_TEXTURE) glTexCoord2d(x / radius, y / radius); 
                    glVertex3f(x, y, step);
                    glEnd();
                }
                if (index2 == 0) colorOfThePrevious = currentColor;
                index2++;
                glEnd();
            }
            index1++; 
        }
        step += height; 
    }
    glColor3f(1.0, 1.0, 1.0);
    glEndList();
}
void animation(){
    if (anim){
        if (t < 1 && !flag) t += 0.0005;
        else flag = true;
        if (t > 0 && flag) t -= 0.0005;
        else flag = false;
        drawWithAnim();
    }else drawCylinder();
}
double lastTime = glfwGetTime();

void CalculateFrameRate() {
    FPS++;
    clock_t fps_time = clock();
    double time = ((double)fps_time) / CLOCKS_PER_SEC - ((double)FPS_time) / CLOCKS_PER_SEC;
    if (time >= 1) {
        cout << "FPS : " << FPS << endl;
        cout << "ms / frame : " << 1000.0/double(FPS) << endl;
        FPS_time = fps_time;
        FPS = 0;
    }
}
int main(){
    if (!glfwInit()){
        return -1;
    }
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "drawing", NULL, NULL);
    glfwSetKeyCallback(window, keyCallback);
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    loadTexture();
    glViewport(0.0f, 0.0f, screenWidth, screenWidth);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(130.0, 1000.0 / 600.0, 0.1, 1000.0);
    //glRotatef(45, 1, 0, 0);
    //glRotatef(45, 0, 1, 0);
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_WIDTH, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    halfW = SCREEN_WIDTH / 2 + 100;
    halfH = SCREEN_HEIGHT / 2 - 100;
    angle_stepsize = 20.0;
    radius = 80;
    height = 256;
    gorizontal_break = 1.0;
    base_break = 2.0;
    glfwSwapInterval(0);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPushMatrix();
        glTranslatef(halfW, halfH, -500.0);
        glRotatef(turnX, 1, 0, 0);
        glRotatef(turnY, 0, 1, 0);
        light_on();
        animation();
        if (IS_TEXTURE) {
            glEnable(GL_TEXTURE_2D);
        }
        else {
            glDisable(GL_TEXTURE_2D);
        }
        glEnd();
        glPopMatrix();
        glCallList(l);
        CalculateFrameRate();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
