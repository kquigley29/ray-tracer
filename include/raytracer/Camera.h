//
// Created by keane on 03/10/2020.
//
#include<Eigen/Eigen>
#include<raytracer/Ray.h>
#include<raytracer/utils.h>

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

using Eigen::Vector3d;

class Camera {
public:
    Camera(const Vector3d& position, const Vector3d& orientation, const double& cam_range,  const std::array<double, 2>& resolution);
    Ray generate_ray(float x, float y);
    std::array<double, 2> get_resolution();
    Vector3d position;
private:

    Vector3d orientation;
    double cam_range;
    std::array<double, 2> resolution;
    double width;
    double height;
    double pwidth;
    Vector3d middle;
    Vector3d left;
    Vector3d up;
};


#endif //RAYTRACER_CAMERA_H
