#include <eigen3/Eigen/Eigen>


#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


struct Material
{
    Eigen::Vector3d colour;

    Material() = default;

    Material(double x, double y, double z)
    : colour(x, y, z)
    { }

    Material(const Eigen::Vector3d& colour)
    : colour(colour)
    { }
};


#endif //RAYTRACER_MATERIAL_H
