//
// Created by keane on 03/10/2020.
//

#include "raytracer/objects/Plane.h"


Plane::Plane(const Eigen::Vector3d &position, const Eigen::Vector3d &normal, const Material &material)
: Object(position, material),
  normal(normal) {}


Eigen::Vector3d Plane::get_normal() const {
    return normal;
}


bool Plane::get_intersection(Intersection &intersection, const Ray &ray) {
    double numerator = this->get_normal().dot(this->get_position() - ray.origin);
    double denominator = this->get_normal().dot(ray.direction);

    if (!denominator) return false;

    double t = numerator / denominator;
    Eigen::Vector3d hit_point = ray.origin + (t * ray.direction);
    intersection = Intersection(hit_point, this->get_normal(), this->get_material());

    return true;
}