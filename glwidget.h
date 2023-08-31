#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <Eigen/Core>


class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

    void drawCube(float a);
    void drawAxes(float length, const QVector3D& origin);

    void drawCubeRotation(const Eigen::MatrixXd& normVectors, const Eigen::Vector3d& principalStresses);

    void setCubeRotation(const float& xRotCube, const float& yRotCube, const float& zRotCube);

    void setXRotation(float angle);
    void setYRotation(float angle);
    void setZRotation(float angle);


public slots:
    void resetView();

private:
    float
        xRot, yRot, zRot,
        zoomFactor,
        xRotCube, yRotCube, zRotCube;
    QPoint mPos;
    QTimer tmr;

    void mousePressEvent(QMouseEvent* mo) override;
    void mouseMoveEvent(QMouseEvent* mo) override;
    void wheelEvent(QWheelEvent* mo) override;

    const GLfloat* getCubeVertices(const float& a);
    const GLuint* getCubeIndices() const;
    const GLfloat* getCubeNormals();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // GLWIDGET_H
