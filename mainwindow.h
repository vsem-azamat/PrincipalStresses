#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QVector>
#include <QString>

#include "glwidget.h"
#include "mohrcircleplot.h"
#include "stresscalculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonCalculate_clicked();
    void on_buttonClearOutput_clicked();

    void on_buttonX_YZ_clicked();

    void on_buttonY_XZ_clicked();

    void on_buttonZ_YZ_clicked();

    void on_buttonClearInput_clicked();

private:
    Ui::MainWindow *ui;
    GLWidget *glWidget;
    MohrCirclePlot *mohrPlot;
    StressValues *stressValues;
};

#endif // MAINWINDOW_H
