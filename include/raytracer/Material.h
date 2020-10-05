#include <eigen3/Eigen/Eigen>


#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


struct Material {
    Eigen::Vector3d colour;
    Eigen::Vector3d emission;

    Material() = default;

    Material(double r, double g, double b, double eR, double eG, double eB)
    : colour(r, g, b) , emission(eR, eG, eB) {}
};


#endif //RAYTRACER_MATERIAL_H
