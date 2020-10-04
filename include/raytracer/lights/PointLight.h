//
// Created by angus on 03/10/2020.
//
#include <raytracer/lights/Light.h>

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H


class PointLight : public Light{
public:
    PointLight(Vector3d position, Vector3d intensity);
    Vector3d calculate_lighting(Intersection& intersection) override;
};

#endif //RAYTRACER_POINTLIGHT_H
