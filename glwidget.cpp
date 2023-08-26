#include "glwidget.h"
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <iostream>


GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setWindowTitle("Principial stresses");

}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    //    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    //    glEnable(GL_MULTISAMPLE);

}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //    glFrustum(-1, 1, -1, 1, 1, 3);
    glOrtho(-1, 1, -1, 1, 1, 3);

}

void GLWidget::paintGL()
{
    initializeOpenGLFunctions();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0, 0, -2);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    drawCube(0.5);
}


void GLWidget::drawCube(float a)
{
    // Cube vertex coordinates
    static const GLfloat ver_cub[] = {
        // Front side
        -a, -a,  a,
        a, -a,  a,
        a,  a,  a,
        -a,  a,  a,
        // Back side
        a, -a, -a,
        -a, -a, -a,
        -a,  a, -a,
        a,  a, -a,
        // Left side
        -a, -a, -a,
        -a, -a,  a,
        -a,  a,  a,
        -a,  a, -a,
        // Right side
        a, -a,  a,
        a, -a, -a,
        a,  a, -a,
        a,  a,  a,
        // Lower side
        -a, -a, -a,
        a, -a, -a,
        a, -a,  a,
        -a, -a,  a,
        // Upper side
        -a,  a,  a,
        a,  a,  a,
        a,  a, -a,
        -a,  a, -a,
    };

    // Indices for each face
    static const GLuint indices[] = {
        0, 1, 2, 3, // Front side
        4, 5, 6, 7, // Back side
        8, 9, 10, 11, // Left side
        12, 13, 14, 15, // Right side
        16, 17, 18, 19, // Lower side
        20, 21, 22, 23, // Upper side
    };

    //    static const GLfloat normals[] = {
    //        0.0f, 0.0f, 1.0f, // Front side
    //        0.0f, 0.0f, -1.0f, // Back side
    //        -1.0f, 0.0f, 0.0f, // Left side
    //        1.0f, 0.0f, 0.0f, // Right side
    //        0.0f, -1.0f, 0.0f, // Lower side
    //        0.0f, 1.0f, 0.0f // Upper side
    //    };

    GLuint vbo, ebo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ver_cub), ver_cub, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Включаем атрибут вершин в шейдере
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    //    glEnable(GL_LINE_STIPPLE);
    //    glLineStipple(10, 0xAAAA); // Маска для пунктирных линий

    glColor3f(0.0f, 0.0f, 0.0f);

    // Рисуем грани куба
    for (int i = 0; i < 6; ++i) {
        glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)(i * 4 * sizeof(GLuint)));
    }

    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void GLWidget::mousePressEvent(QMouseEvent* mo)
{
    mPos = mo->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* mo)
{
    xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
    yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
    update();
}
