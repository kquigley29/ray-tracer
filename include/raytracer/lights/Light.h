//
// Created by angus on 03/10/2020.
//

#include<eigen3/Eigen/Eigen>
#include<raytracer/Intersection.h>
#include "raytracer/utils.h"

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

using Eigen::Vector3d;

class Light {
public:
    Light(Vector3d intensity);
    virtual Vector3d calculate_lighting(Intersection& intersection);
    Vector3d intensity;
    Vector3d position;
};


#endif //RAYTRACER_LIGHT_H
