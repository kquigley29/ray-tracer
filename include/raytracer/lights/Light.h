#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include <eigen3/Eigen/Eigen>
#include<raytracer/Intersection.h>
#include "raytracer/utils.h"


class Light {
public:
    explicit Light(const Eigen::Vector3d& intensity);
    explicit Light(const Eigen::Vector3d& position, const Eigen::Vector3d& intensity);

    virtual Eigen::Vector3d calculate_lighting(Intersection& intersection);

    Eigen::Vector3d get_intensity();
    Eigen::Vector3d get_position();

private:
    Eigen::Vector3d intensity;
    Eigen::Vector3d position;
};


#endif //RAYTRACER_LIGHT_H
