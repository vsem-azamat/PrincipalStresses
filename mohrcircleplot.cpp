#include "mohrcircleplot.h"
#include <Eigen/Core>

MohrCirclePlot::MohrCirclePlot(QWidget *parent)
    : parentWidget(parent)
{
    if (parentWidget)
    {
        plot = new QCustomPlot(parentWidget);
        plot->setGeometry(0, 0, 350, 350);

        // Set description
        plot->xAxis->setLabel("σ [MPa]");
        plot->yAxis->setLabel("τ [MPa]");
    }
}

void MohrCirclePlot::plotMohrCircle(const Eigen::Vector3d& principalStresses)
{
    if (!plot)
        return;

    // Clear old plot
    plot->clearPlottables();
    plot->clearItems();
    plot->setFont(QFont("Helvetica", 10));

    float sigma1 = principalStresses[0];
    float sigma2 = principalStresses[1];
    float sigma3 = principalStresses[2];

    float center12 = (sigma1 + sigma2) / 2;
    float center23 = (sigma2 + sigma3) / 2;
    float center13 = (sigma1 + sigma3) / 2;

    float radius12 = abs(sigma1 - sigma2) / 2;
    float radius23 = abs(sigma2 - sigma3) / 2;
    float radius13 = abs(sigma1 - sigma3) / 2;

    plot->addGraph();

    // Plot circles
    QCPItemEllipse *mohrCircle13 = new QCPItemEllipse(plot);
    mohrCircle13->setBrush(QBrush(Qt::Dense6Pattern));
    mohrCircle13->topLeft->setCoords(center13-radius13, radius13);
    mohrCircle13->bottomRight->setCoords(center13+radius13, -radius13);

    QCPItemEllipse *mohrCircle12 = new QCPItemEllipse(plot);
    mohrCircle12->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    mohrCircle12->topLeft->setCoords(center12-radius12, radius12);
    mohrCircle12->bottomRight->setCoords(center12+radius12, -radius12);

    QCPItemEllipse *mohrCircle23 = new QCPItemEllipse(plot);
    mohrCircle23->setBrush(QBrush(Qt::white));
    mohrCircle23->topLeft->setCoords(center23-radius23, radius23);
    mohrCircle23->bottomRight->setCoords(center23+radius23, -radius23);

    // Set sigma annotations
    QCPItemText *textSigma1 = new QCPItemText(plot);
    textSigma1->setPositionAlignment(Qt::AlignLeft);
    textSigma1->setText("σ1");
    textSigma1->position->setCoords(sigma1, 0);

    QCPItemText *textSigma2 = new QCPItemText(plot);
    textSigma2->setPositionAlignment(Qt::AlignLeft);
    textSigma2->setText("σ2");
    textSigma2->position->setCoords(sigma2, 0);

    QCPItemText *textSigma3 = new QCPItemText(plot);
    textSigma3->setPositionAlignment(Qt::AlignRight);
    textSigma3->setText("σ3");
    textSigma3->position->setCoords(sigma3, 0);

    // Set tau max annotations
    QCPItemText *textTauMax = new QCPItemText(plot);
    textTauMax->setPositionAlignment(Qt::AlignBottom);
    textTauMax->setText("τ max");
    textTauMax->position->setCoords(0, radius13);

    QCPItemLine *tauMaxLine = new QCPItemLine(plot);
    tauMaxLine->start->setCoords(center13, radius13);
    tauMaxLine->end->setCoords(0, radius13);

    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::DashLine);
    tauMaxLine->setPen(pen);

    // Set axes ranges
    plot->xAxis->setRange(center13-radius13*1.3, center13+radius13*1.3);
    plot->yAxis->setRange(-radius13*1.3, radius13*1.3);

    // Replot the graph
    plot->replot();
}
