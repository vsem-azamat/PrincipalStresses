#include "mohrcircleplot.h"

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

void MohrCirclePlot::draw(double sigma1, double sigma2, double sigma3)
{
    if (!plot)
        return;

    sigma1 = 60;
    sigma2 = 0;
    sigma3 = -20;

    float center12 = (sigma1 + sigma2) / 2;
    float center23 = (sigma2 + sigma3) / 2;
    float center13 = (sigma1 + sigma3) / 2;

    float radius12 = (sigma1 - sigma2) / 2;
    float radius23 = (sigma2 - sigma3) / 2;
    float radius13 = (sigma1 - sigma3) / 2;

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
        textSigma1->setFont(QFont("Helvetica", 10));
    textSigma1->position->setCoords(sigma1, 0);

    QCPItemText *textSigma2 = new QCPItemText(plot);
    textSigma2->setPositionAlignment(Qt::AlignLeft);
    textSigma2->setText("σ2");
        textSigma2->setFont(QFont("Helvetica", 10));
    textSigma2->position->setCoords(sigma2, 0);

    QCPItemText *textSigma3 = new QCPItemText(plot);
    textSigma3->setPositionAlignment(Qt::AlignRight);
    textSigma3->setText("σ3");
        textSigma3->setFont(QFont("Helvetica", 10));
    textSigma3->position->setCoords(sigma3, 0);

    // Set tau max annotations
    QCPItemText *textTauMax = new QCPItemText(plot);
    textTauMax->setPositionAlignment(Qt::AlignBottom);
    textTauMax->setText("τ max");
        textTauMax->setFont(QFont("Helvetica", 10));
    textTauMax->position->setCoords(0, radius13);

    QCPItemLine *tauMaxLine = new QCPItemLine(plot);
    tauMaxLine->start->setCoords(center13, radius13);
    tauMaxLine->end->setCoords(0, radius13);

    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::DashLine);
    tauMaxLine->setPen(pen);

    // Set axes ranges
    plot->xAxis->setRange(sigma3*1.5, sigma1*1.5);
    plot->yAxis->setRange(-radius13*1.5, radius13*1.5);

    // Replot the graph
    plot->replot();
}
