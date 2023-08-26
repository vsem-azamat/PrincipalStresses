#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <glwidget.h>
#include <mohrcircleplot.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //    connect(ui->calculateButton, &QPushButton::clicked, glWidget, &GLWidget::drawMainCube);
    //    connect(ui->calculateButton, &QPushButton::clicked, this, &MainWindow::on_calculateButton_clicked);
    mohrPlot = new MohrCirclePlot(ui->widget_2);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete glWidget;
    delete mohrPlot;
}

void MainWindow::on_calculateButton_clicked()
{
    //    float sigmaX = ui->inputSigmaX->text().toFloat();
    //    float sigmaY = ui->inputSigmaY->text().toFloat();
    //    float sigmaZ = ui->inputSigmaZ->text().toFloat();

    //    float tauX = ui->inputTauX->text().toFloat();
    //    float tauY = ui->inputTauY->text().toFloat();
    //    float tauZ = ui->inputTauZ->text().toFloat();
    //    MohrCirclePlot->draw();

    mohrPlot->draw(0,0,0);
}

