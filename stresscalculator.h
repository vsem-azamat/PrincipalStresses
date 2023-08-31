#ifndef STRESSCALCULATOR_H
#define STRESSCALCULATOR_H

#include <Eigen/Core>

struct StressValues {
    float sigmaX = 0;
    float sigmaY = 0;
    float sigmaZ = 0;
    float tauX = 0;
    float tauY = 0;
    float tauZ = 0;
};

class StressCalculator {
public:
    static Eigen::Matrix3d convertToStressMatrix(const StressValues& stressValues);
    static Eigen::Vector3d calcPrincipalStresses(const StressValues& stressValues);
    static Eigen::Matrix3d calcNormVectors(const StressValues& stressValues);
};

#endif // STRESSCALCULATOR_H
