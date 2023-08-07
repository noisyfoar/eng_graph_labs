#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math_3d.h"


GLuint VBO; // переменная, хранящая указатель на буфер данныхj


static void RenderSceneCB()//функция рисования
{
    glClear(GL_COLOR_BUFFER_BIT);//очистка буфера кадра

    glEnableVertexAttribArray(0); // включение атрибута вершины
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//привязка VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//наполнение буфера данными

    glDrawArrays(GL_TRIANGLES, 0, 3);//функция отрисовки

    glDisableVertexAttribArray(0);//отключение атрибута вершины

    glutSwapBuffers();//функция, меняющая фоновый буфер и буфер кадра местами
}


static void InitializeGlutCallbacks()//установка функции рисования в окне
{
    glutDisplayFunc(RenderSceneCB);
}

static void CreateVertexBuffer()//создание массива из 3 векторов
{
    Vector3f Vertices[3];
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);// задание положения первой точки
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f); // задание положения второй точки
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f); // задание положения третьей точки

    glGenBuffers(1, &VBO);//генерация объекта
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//привязка VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);//наполнение буфера данными
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv); // инициализация GLUT - библиотеки
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //включаем двойную буферизацию и буфер цвета

    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Lesson 3"); //вызывает функцию для работы в оконной системе

    InitializeGlutCallbacks();

    GLenum res = glewInit(); //инициализация GLEW и проверка его на ошибки
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //устанавливает цвет, который будет использован во время очистки буфера кадра

    CreateVertexBuffer();//создает буфер вершин

    glutMainLoop();//передает контроль GLUT'у, который начнет свой собственный цикл

    return 0;
}