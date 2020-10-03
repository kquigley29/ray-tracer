//
// Created by angus on 03/10/2020.
//
#include <raytracer/Light.h>

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H


class PointLight : public Light{
    PointLight(Vector3d position, Vector3d intensity);
    Vector3d calculate_lighting() override;

private:
    Vector3d position;
};

#endif //RAYTRACER_POINTLIGHT_H
