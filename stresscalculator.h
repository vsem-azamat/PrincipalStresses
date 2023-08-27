#ifndef STRESSCALCULATOR_H
#define STRESSCALCULATOR_H

#include <Eigen/Core>

struct StressValues {
    double sigmaX = 0;
    double sigmaY = 0;
    double sigmaZ = 0;
    double tauX = 0;
    double tauY = 0;
    double tauZ = 0;
};

class StressCalculator {
public:
    static Eigen::Matrix3d convertToStressMatrix(const StressValues& stressValues);
    static Eigen::Vector3d calcPrincipalStresses(const StressValues& stressValues);
    static Eigen::Matrix3d calcNormVectors(const StressValues& stressValues);
//    StressCalculator();
};

#endif // STRESSCALCULATOR_H
