//
// Created by angus on 03/10/2020.
//

#include<eigen3/Eigen/Eigen>

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

using Eigen::Vector3d;

class Light {
public:
    Light(Vector3d intensity) : intensity(intensity){};
    virtual Vector3d calculate_lighting();
    Vector3d intensity;
};


#endif //RAYTRACER_LIGHT_H
