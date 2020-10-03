//
// Created by keane on 03/10/2020.
//

#include<raytracer/Camera.h>

Camera::Camera(const Vector3d& position, const Vector3d& orientation, const double& cam_range, const std::vector<double>& resolution) {
    Vector3d i(1,0,0);
    Vector3d j(0,1,0);
    Vector3d k(0,0,1);

    this->position = position;
    this->orientation = orientation;
    this->cam_range = cam_range;
    this->resolution = resolution;

    this->width = resolution[0] / resolution[1];
    this->height = 1;
    this->pwidth = 1 / resolution[1];
    this->middle = position + (orientation * cam_range);
    this->left = k.cross(orientation).normalized();
    this->up = orientation.cross(left).normalized();

}

Ray Camera::generate_ray(float x, float y) {
    Vector3d pix_pos = this->middle - (this->pwidth * x * this->left) - (this->pwidth * y * this->up);
    pix_pos += this->up * this->height / 2;
    pix_pos += this->left * this->width / 2;
    Vector3d dray = (pix_pos - this->position).normalized();

    return Ray(this->position, dray);

}