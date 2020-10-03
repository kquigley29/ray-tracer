//
// Created by angus on 03/10/2020.
//
#include<eigen3/Eigen/Eigen>

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#endif //RAYTRACER_RAY_H

using Eigen::Vector3d;

struct Ray{
    Vector3d origin;
    Vector3d direction;
    Ray(Vector3d origin, Vector3d direction){
        this->origin = origin;
        this->direction = direction;
    }
};