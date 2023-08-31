#include "stresscalculator.h"
#include <unsupported/Eigen/Polynomials>
#include <iostream>

using namespace Eigen;

Matrix3d StressCalculator::convertToStressMatrix(const StressValues& stressValues)
{
    MatrixXd stressMatrix(3,3);
    stressMatrix <<
        stressValues.sigmaX,    stressValues.tauZ,      stressValues.tauY,
        stressValues.tauZ,      stressValues.sigmaY,    stressValues.tauX,
        stressValues.tauY,      stressValues.tauX,      stressValues.sigmaZ;
    return stressMatrix;
}

Vector3d StressCalculator::calcPrincipalStresses(const StressValues& stressValues)
{
    Matrix3d stressMatrix = convertToStressMatrix(stressValues);
    SelfAdjointEigenSolver<MatrixXd> solver(stressMatrix);
    Vector3d principalStresses = solver.eigenvalues().real();
    return principalStresses;
}

Matrix3d StressCalculator::calcNormVectors(const StressValues& stressValues)
{
    Matrix3d stressMatrix = convertToStressMatrix(stressValues);
    SelfAdjointEigenSolver<MatrixXd> solver(stressMatrix);
    MatrixXd planeVectors = solver.eigenvectors().real();
    return planeVectors;
}
