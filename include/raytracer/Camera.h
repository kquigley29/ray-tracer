#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include <Eigen/Eigen>
#include <raytracer/Ray.h>
#include <raytracer/utils.h>
#include <random>


using Eigen::Vector3d;

class Camera {
public:
    Camera();
    Camera(const Vector3d& position, const Vector3d& orientation, const double& cam_range,  const std::array<double, 2>& resolution);

    Ray generate_ray(float x, float y);

    Eigen::Vector3d get_position() const;
    std::array<double, 2> get_resolution() const;

private:

    Vector3d position;
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
