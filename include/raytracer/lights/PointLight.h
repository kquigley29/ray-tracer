#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H


#include <raytracer/lights/Light.h>


class PointLight : public Light {
public:
    PointLight(const Eigen::Vector3d& position, const Eigen::Vector3d& intensity);

    Eigen::Vector3d calculate_lighting(Intersection& intersection) override;
};


#endif //RAYTRACER_POINTLIGHT_H
