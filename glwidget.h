#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QTimer>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

    void drawCubeTest(float a);
    void drawCube(float a);

private:
    float xRot, yRot, zRot;
    QPoint mPos;
    QTimer tmr;
    void mousePressEvent(QMouseEvent* mo) override;
    void mouseMoveEvent(QMouseEvent* mo) override;

    const GLfloat* getCubeVertices(const float& a);
    const GLuint* getCubeIndices() const;
    const GLfloat* getCubeNormals();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // GLWIDGET_H
