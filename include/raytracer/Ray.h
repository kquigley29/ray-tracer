//
// Created by angus on 03/10/2020.
//
#include<eigen3/Eigen/Eigen>
#include <utility>


#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


struct Ray {
    Eigen::Vector3d origin;
    Eigen::Vector3d direction;

    Ray(Eigen::Vector3d& origin, Eigen::Vector3d& direction){
        this->origin = origin;
        this->direction = direction;
    }
};


#endif //RAYTRACER_RAY_H


