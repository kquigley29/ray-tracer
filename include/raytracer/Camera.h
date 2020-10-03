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
    explicit Camera(const Vector3d& position, const Vector3d& orientation, const double& cam_range,  const std::vector<double>& resolution);
    Ray generate_ray(float x, float y);
private:
    Vector3d position;
    Vector3d orientation;
    double cam_range;
    std::vector<double> resolution;
    double width;
    double height;
    double pwidth;
    Vector3d middle;
    Vector3d left;
    Vector3d up;
};


#endif //RAYTRACER_CAMERA_H
