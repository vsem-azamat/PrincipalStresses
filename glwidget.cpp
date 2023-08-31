#include "glwidget.h"

#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QMatrix4x4>
#include <Eigen/Core>
#include <iostream>
#include <cmath>

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setWindowTitle("Principial stresses");
    xRot = yRot = zRot = 0.0f; // Initialize camera rotation angles
    xRotCube = yRotCube = zRotCube = 0; // Initialize cube rotation angles
    zoomFactor = 1.0f; // Initialize the zoom factor to 1.0
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
    glEnable(GL_COLOR_MATERIAL);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, -2, 5);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(zoomFactor, zoomFactor, zoomFactor); // Apply the zoom scale

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    float cubeSize = 0.5;
    drawAxes(1.0, QVector3D(0, 0, 0));

    // Rotate a cube about a normal vectors
    glRotatef(this->zRotCube, 0, 0, 1);
    glRotatef(this->yRotCube, 0, 1, 0);
    glRotatef(this->xRotCube, 1, 0, 0);

    drawCube(cubeSize);
}

void GLWidget::drawCube(float a)
{
    static const GLfloat cubeVertices[] = {
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

    static const GLuint cubeIndices[] = {
        0, 1, 2, 3, // Front side
        4, 5, 6, 7, // Back side
        8, 9, 10, 11, // Left side
        12, 13, 14, 15, // Right side
        16, 17, 18, 19, // Lower side
        20, 21, 22, 23, // Upper side
    };

    GLuint vbo, ebo;

    // Generate VBO and EBO as before
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    // Enable vertex attribute array for cube vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glColor3f(0.0f, 0.0f, 0.0f);

    // Draw cube's faces
    for (int i = 0; i < 6; ++i) {
        glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)(i * 4 * sizeof(GLuint)));
    }

    // Disable vertex attribute array
    glDisableVertexAttribArray(0);

    // Delete VBO and EBO
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void GLWidget::drawAxes(float length, const QVector3D& origin)
{
    // Draw X-axis
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glBegin(GL_LINES);
    glVertex3f(-origin.x(), -origin.y(), -origin.z());
    glVertex3f(origin.x() + length, -origin.y(), -origin.z());
    glEnd();

    // Draw Y-axis
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glBegin(GL_LINES);
    glVertex3f(-origin.x(), -origin.y(), -origin.z());
    glVertex3f(-origin.x(), origin.y() + length, -origin.z());
    glEnd();

    // Draw Z-axis
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glBegin(GL_LINES);
    glVertex3f(-origin.x(), -origin.y(), -origin.z());
    glVertex3f(-origin.x(), -origin.y(), origin.z() + length);
    glEnd();
}

void GLWidget::setCubeRotation(const float& xRotCube, const float& yRotCube, const float& zRotCube)
{
    this->xRotCube = std::isnan(xRotCube) || std::fabs(xRotCube) < 1e-6 ? 0.0f : xRotCube;
    this->yRotCube = std::isnan(yRotCube) || std::fabs(yRotCube) < 1e-6 ? 0.0f : yRotCube;
    this->zRotCube = std::isnan(zRotCube) || std::fabs(zRotCube) < 1e-6 ? 0.0f : zRotCube;

    update();
}

void GLWidget::setXRotation(float angle)
{
    xRot = angle;
    update();
}

void GLWidget::setYRotation(float angle)
{
    yRot = angle;
    update();
}

void GLWidget::setZRotation(float angle)
{
    zRot = angle;
    update();
}


void GLWidget::drawCubeRotation(const Eigen::MatrixXd& normVectors, const Eigen::Vector3d& principalStresses)
{
    Eigen::Vector3d principalStressesSorted;
    // Creating indexes for sort principalStresses
    std::vector<size_t> indexes(principalStresses.size());
    for (size_t i = 0; i < indexes.size(); ++i) {
        indexes[i] = i;
    }

    // Sorting indexes BIG->SMALL principalStresses
    std::sort(indexes.begin(), indexes.end(), [&principalStresses](size_t i, size_t j) {
        return principalStresses[i] > principalStresses[j];
    });

    // Creating matrix for replace normVectors
    Eigen::MatrixXd sortedNormVectors(normVectors.rows(), normVectors.cols());
    for (size_t i = 0; i < indexes.size(); ++i) {
        sortedNormVectors.col(i) = normVectors.col(indexes[i]);
    }

    // Update principalStresses with for indexes
    for (size_t i = 0; i < indexes.size(); ++i) {
        principalStressesSorted[i] = principalStresses[indexes[i]];
    }

    // Separate vectors
    const Eigen::Vector3d vector1 = sortedNormVectors.col(0);
    const Eigen::Vector3d vector2 = sortedNormVectors.col(1);

    const float phi = std::acos(std::sqrt(vector1[0]*vector1[0] + vector1[2]*vector1[2]));
    const float betta = std::acos(std::sqrt(vector1[0]*vector1[0] + vector1[1]*vector1[1]));
    const float gamma = std::acos(std::sqrt(vector2[0]*vector2[0] + vector2[1]*vector2[1]));

    const float phi_deg = phi * 180 / M_PI;
    const float betta_deg = betta * 180 / M_PI;
    const float gamma_deg = gamma * 180 / M_PI;

    setCubeRotation(gamma_deg, betta_deg, phi_deg);
}

void GLWidget::resetView()
{
    xRot = yRot = zRot = 0.0f; // Reset rotation angles
    zoomFactor = 1.0f; // Reset zoom factor
    update();
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

void GLWidget::wheelEvent(QWheelEvent *mo)
{
    // Get the angle delta from the mouse wheel
    int angleDelta = mo->angleDelta().y();

    // Adjust the zoom factor based on the angle delta
    zoomFactor += angleDelta / 1200.0f; // Adjust this value as needed for your scene

    // Ensure a minimum and maximum zoom factor if desired
    if (zoomFactor < 0.1f)
        zoomFactor = 0.1f;
    if (zoomFactor > 2.0f)
        zoomFactor = 2.0f;

    update();
}

