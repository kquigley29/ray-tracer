#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include <eigen3/Eigen/Eigen>
#include <utility>


struct Ray
{
    Eigen::Vector3d origin;
    Eigen::Vector3d direction;

    Ray(const Eigen::Vector3d& origin, const Eigen::Vector3d& direction)
    : origin(origin)
    , direction(direction)
    { }
};


#endif //RAYTRACER_RAY_H