#include<raytracer/Camera.h>


Camera::Camera() {}


Camera::Camera(const Vector3d& position, const Vector3d& orientation, const double& cam_range, const std::array<double, 2>& resolution)
: position(position)
, orientation(orientation)
, cam_range(cam_range)
, resolution(resolution)
{
    Vector3d i(1,0,0);
    Vector3d j(0,1,0);
    Vector3d k(0,0,1);

    this->width = resolution[0] / resolution[1];
    this->height = 1;
    this->pwidth = 1 / resolution[1];
    this->middle = position + (orientation * cam_range);
    this->left = k.cross(orientation).normalized();
    this->up = orientation.cross(left).normalized();
}


Ray Camera::generate_ray(float x, float y) {
    Vector3d pix_pos = this->middle - (this->pwidth * x * this->left) - (this->pwidth * y * this->up);
    pix_pos += this->up * this->height / 2 + this->left * this->width / 2;
    Ray ray(this->position, pix_pos - this->position);
    return ray;
}


Eigen::Vector3d Camera::get_position() const {
    return this->position;
}


std::array<double, 2> Camera::get_resolution() const {
    return this->resolution;
}
