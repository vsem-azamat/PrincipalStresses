#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mohrPlot = new MohrCirclePlot(ui->widget_2);
    stressValues = new StressValues();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete glWidget;
    delete mohrPlot;
    delete stressValues;
}

void MainWindow::on_buttonCalculate_clicked()
{
    stressValues->sigmaX = ui->inputSigmaX->text().toFloat();
    stressValues->sigmaY = ui->inputSigmaY->text().toFloat();
    stressValues->sigmaZ = ui->inputSigmaZ->text().toFloat();
    stressValues->tauX = ui->inputTauX->text().toFloat();
    stressValues->tauY = ui->inputTauY->text().toFloat();
    stressValues->tauZ = ui->inputTauZ->text().toFloat();

    Eigen::Vector3d principalStresses = StressCalculator::calcPrincipalStresses(*stressValues);

    // Console output
    QString textOutput = "===== Principal stresses: =====\n";
    textOutput += QString("σ1 = %1 MPa\n").arg(principalStresses[0]);
    textOutput += QString("σ2 = %1 MPa\n").arg(principalStresses[1]);
    textOutput += QString("σ3 = %1 MPa\n").arg(principalStresses[2]);
    textOutput += QString("τ max = %1 MPa").arg((principalStresses[0] - principalStresses[2]) / 2);

    QString currentText = ui->textBrowser->toPlainText();
    QString newText = textOutput + "\n" + currentText;
    ui->textBrowser->setText(newText);

    // Plot output
    mohrPlot->plotMohrCircle(principalStresses);

    // OpenGL output
    ui->widget->drawCubeTest(0);
}


void MainWindow::on_buttonClearOutput_clicked()
{
    ui->textBrowser->clear();
}

