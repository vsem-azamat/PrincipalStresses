#ifndef MOHRCIRCLEPLOT_H
#define MOHRCIRCLEPLOT_H

#include <QWidget>
#include <qcustomplot.h>

class MohrCirclePlot
{
public:
    MohrCirclePlot(QWidget *parent = nullptr);

    void draw(double sigma1, double sigma2, double sigma3);

private:
    QWidget *parentWidget = nullptr;
    QCustomPlot *plot = nullptr;
};

#endif // MOHRCIRCLEPLOT_H
