#ifndef RAY_TRACER_UTILS_H
#define RAY_TRACER_UTILS_H


#include<eigen3/Eigen/Eigen>


#define I_UNIT_VECTOR Eigen::Vector3d(1, 0, 0)
#define J_UNIT_VECTOR Eigen::Vector3d(0, 1, 0)
#define K_UNIT_VECTOR Eigen::Vector3d(0, 0, 1)


Eigen::Vector3d clamp(Eigen::Vector3d vec);


#endif //RAY_TRACER_UTILS_H




