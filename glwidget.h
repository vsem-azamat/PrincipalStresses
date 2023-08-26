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

private:
    float xRot, yRot, zRot;
    QPoint mPos;
    QTimer tmr;
    void drawCube(float a);
    void drawCubeTest(float a);
    void mousePressEvent(QMouseEvent* mo) override;
    void mouseMoveEvent(QMouseEvent* mo) override;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // GLWIDGET_H
