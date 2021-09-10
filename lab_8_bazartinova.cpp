#define GLEW_STATIC
#include <GL/glew.h>
#include "iostream"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
const GLuint WIDTH = 800, HEIGHT = 800;
GLfloat x = 0.f, y = 0.f, z = 0.f;
GLfloat scale = 1.f;
GLfloat a = 0.f, b = 0.f, c = 0.f;
bool PolygonMode = true;
GLuint VBO, VAO;
glm::mat4 projection = {
    {1, 0, 0, 0.5},
    {0, 1, 0, 0},
    {0, 0, 1, 0.5},
    {0, 0, 0, 1}};

glm::mat4 big_cube, small_cube;
const GLchar *vertexShaderSource = "#version 330\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 fragmentColor;\n"
"uniform mat4 big_cube;\n"
"void main()\n"
"{\n"
"gl_Position = big_cube * vec4(position, 1.0f);\n"
"fragmentColor = color;"
"}\0";

const GLchar *fragmentShaderSource = "#version 330\n"
"in vec3 fragmentColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(fragmentColor, 1.0);\n"
"}\0";

void make_cube(double edge) {
    GLdouble vertices[] = {
        // FRONT
        edge, edge, -edge, 1., 0., 0.,
        -edge, -edge, -edge, 1., 0., 0.,
        -edge, edge, -edge, 1., 0., 0.,
        
        edge, edge, -edge, 1., 0., 0.,
        edge, -edge, -edge, 1., 0., 0.,
        -edge, -edge, -edge, 1., 0., 0.,
        //LEFT
        -edge, -edge, -edge, 0., 1., 0.,
        -edge, -edge, edge, 0., 1., 0.,
        -edge, edge, edge, 0., 1., 0.,
        
        -edge, -edge, -edge, 0., 1., 0.,
        -edge, edge, edge, 0., 1., 0.,
        -edge, edge, -edge, 0., 1., 0.,
        //BOTTOM
        edge, -edge, edge, 0., 0., 1.,
        -edge, -edge, -edge, 0., 0., 1.,
        edge, -edge, -edge, 0., 0., 1.,
        
        edge, -edge, edge, 0., 0., 1.,
        -edge, -edge, edge, 0., 0., 1.,
        -edge, -edge, -edge, 0., 0., 1.,
        //RIGHT
        edge, edge, edge, 1., 0., 1.,
        edge, -edge, -edge, 1., 0., 1.,
        edge, edge, -edge, 1., 0., 1.,
        
        edge, -edge, -edge, 1., 0., 1.,
        edge, edge, edge, 1., 0., 1.,
        edge, -edge, edge, 1., 0., 1.,
        // TOP
        edge, edge, edge, 1., 1., 0.,
        edge, edge, -edge, 1., 1., 0.,
        -edge, edge, -edge, 1., 1., 0.,
        
        edge, edge, edge, 1., 1., 0.,
        -edge, edge, -edge, 1., 1., 0.,
        -edge, edge, edge, 1., 1., 0.,
        // BACK
        -edge, edge, edge, 0., 1., 1.,
        -edge, -edge, edge, 0., 1., 1.,
        edge, -edge, edge, 0., 1., 1.,
        
        edge, edge, edge, 0., 1., 1.,
        -edge, edge, edge, 0., 1., 1.,
        edge, -edge, edge, 0., 1., 1.,
    };
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(GLdouble), (GLvoid *) 0);
    glEnableVertexAttribArray(0);//включаю массив атритутов
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(GLdouble), (GLvoid *) (3 * sizeof(GLdouble)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void rebuild() {
    big_cube = glm::scale(projection, glm::vec3(scale, scale, scale));
    big_cube = glm::translate(big_cube, glm::vec3(x, y, z));
    big_cube = glm::rotate(big_cube, a, glm::vec3(0, 1, 0));
    big_cube = glm::rotate(big_cube, b, glm::vec3(1, 0, 0));
    big_cube = glm::rotate(big_cube, c, glm::vec3(0, 0, 1));
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    const GLfloat rotation = 0.1f;
    const GLfloat move = 0.01f;
    const GLfloat scale_coef = 0.01f;
    
    if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        a += rotation;
    }
    if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        a -= rotation;
    }
    if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        b += rotation;
    }
    if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        b -= rotation;
    }
    if (key == GLFW_KEY_END && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        c -= rotation;
    }
    if (key == GLFW_KEY_LEFT_SHIFT && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        c -= rotation;
    }
    if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        x -= move;
    }
    if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        x += move;
    }
    if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        y += move;
    }
    if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        y -= move;
    }
    if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        z -= move;
    }
    if (key == GLFW_KEY_Z && (action == GLFW_REPEAT || action == GLFW_PRESS)) {
        z += move;
    }
    if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) {
        scale += scale_coef;
    }
    if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
        scale -= scale_coef;
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        if (PolygonMode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        PolygonMode = !PolygonMode;
    }
    rebuild();
}
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Lab8", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glewInit();
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // ! Создаем вершинный шейдер
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // ! Передаем исходный код
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // ! Компилируем шейдер
    glCompileShader(vertexShader);
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // ! Создаем программу и прикрепляем шейдеры к ней
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    GLint success;
    GLchar infoLog[512];
    // ! Линкуем шейдерную программу
    glLinkProgram(shaderProgram);
    // ! Проверяем статус сборки
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER PROGRAM LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    GLuint matrix = glGetUniformLocation(shaderProgram, "big_cube");
    make_cube(0.3f);
    rebuild();
    
    small_cube = glm::translate(projection, glm::vec3(-0.5, -0.5, 0.));
    small_cube = glm::scale(small_cube, glm::vec3(0.1, 0.1, 0.1));

    glUseProgram(shaderProgram);
    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Передать наши трансформации в текущий шейдер
        glUniformMatrix4fv(matrix, 1, GL_FALSE, &big_cube[0][0]);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glUniformMatrix4fv(matrix, 1, GL_FALSE, &small_cube[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}