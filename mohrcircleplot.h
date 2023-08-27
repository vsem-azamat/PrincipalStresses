#ifndef MOHRCIRCLEPLOT_H
#define MOHRCIRCLEPLOT_H

#include <QWidget>
#include <qcustomplot.h>
#include <Eigen/Core>

class MohrCirclePlot
{
public:
    MohrCirclePlot(QWidget *parent = nullptr);

    void plotMohrCircle(const Eigen::Vector3d& principalStresses);

private:
    QWidget *parentWidget = nullptr;
    QCustomPlot *plot = nullptr;
};

#endif // MOHRCIRCLEPLOT_H
