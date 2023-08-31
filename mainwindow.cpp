#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"

#include <Eigen/Core>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mohrPlot = new MohrCirclePlot(ui->widget_2);
    stressValues = new StressValues();
    glWidget = ui->widget;

    connect(ui->buttonResetView, &QPushButton::clicked, ui->widget, &GLWidget::resetView);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mohrPlot;
    delete stressValues;
    delete glWidget;
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

    // OpenGL rotate cube
    Eigen::MatrixXd normVectors = StressCalculator::calcNormVectors(*stressValues);
    glWidget->drawCubeRotation(normVectors, principalStresses);

    // Plot Mohr circle
    std::sort(std::begin(principalStresses), std::end(principalStresses), std::greater<double>());
    mohrPlot->plotMohrCircle(principalStresses);

    // Console output
    QString textOutput = "===== Principal stresses: =====\n";
    textOutput += QString("σ1 = %1 MPa\n").arg(principalStresses[0]);
    textOutput += QString("σ2 = %1 MPa\n").arg(principalStresses[1]);
    textOutput += QString("σ3 = %1 MPa\n").arg(principalStresses[2]);
    textOutput += QString("τ max = %1 MPa").arg((principalStresses[0] - principalStresses[2]) / 2);

    QString currentText = ui->textBrowser->toPlainText();
    QString newText = textOutput + "\n" + currentText;
    ui->textBrowser->setText(newText);
}

void MainWindow::on_buttonClearOutput_clicked()
{
    ui->textBrowser->clear();
}

void MainWindow::on_buttonClearInput_clicked()
{
    ui->inputSigmaX->clear();
    ui->inputSigmaY->clear();
    ui->inputSigmaZ->clear();
    ui->inputTauX->clear();
    ui->inputTauY->clear();
    ui->inputTauZ->clear();
}

void MainWindow::on_buttonX_YZ_clicked()
{
    ui->widget->resetView();
    ui->widget->setXRotation(90.0f);
    ui->widget->setYRotation(0.0f);
    ui->widget->setZRotation(0.0f);
}

void MainWindow::on_buttonY_XZ_clicked()
{
    ui->widget->resetView();
    ui->widget->setXRotation(0.0f);
    ui->widget->setYRotation(90.0f);
    ui->widget->setZRotation(0.0f);
}

void MainWindow::on_buttonZ_YZ_clicked()
{
    ui->widget->resetView();
    ui->widget->setXRotation(0.0f);
    ui->widget->setYRotation(0.0f);
    ui->widget->setZRotation(90.0f);
}


