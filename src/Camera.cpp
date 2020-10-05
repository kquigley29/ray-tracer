#include<raytracer/Camera.h>
#include<iostream>
#include "raytracer/utils.h"


Camera::Camera(const Vector3d& position, const Vector3d& orientation, const double& cam_range, const DOFData& dofData,const std::array<double, 2>& resolution)
: position(position)
, orientation(orientation)
, cam_range(cam_range)
, resolution(resolution)
, dofData(dofData)

{
    std::srand(time(NULL));
    double scalar = dofData.focal_length/cam_range;


    this->width = (resolution[0] / resolution[1]) * scalar;
    this->height = 1 * scalar;
    this->pwidth = (1 / resolution[1]) * scalar;
    this->middle = position + (orientation * cam_range * scalar);


    this->left = K_UNIT_VECTOR.cross(orientation).normalized();
    this->up = orientation.cross(left).normalized();
}


Ray Camera::generate_ray(float x, float y) {
    Vector3d pix_pos = this->middle - (this->pwidth * x * this->left) - (this->pwidth * y * this->up);
    pix_pos += this->up * this->height / 2 + this->left * this->width / 2;

    double randX = (((fast_rand()) * 2 -1) * this->dofData.aperture);
    double randY = (((fast_rand()) * 2 - 1) * this->dofData.aperture);

    Vector3d orig = this->position + (this->up * randY) + (this->left*randX);

//    std::cout << "randX: " << randX << "\n";
//    std::cout << "randY: " << randY << "\n";


    Ray ray(orig, pix_pos - orig);
    return ray;
}


Eigen::Vector3d Camera::get_position() {
    return this->position;
}


std::array<double, 2> Camera::get_resolution() {
    return this->resolution;
}
