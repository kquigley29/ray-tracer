//
// Created by keane on 03/10/2020.
//
#include <iostream>
#include "raytracer/objects/Sphere.h"


Sphere::Sphere(const Eigen::Vector3d &position, const double &radius, const Material& material)
: Object(position, material),
  radius(radius) {}


Sphere::Sphere(const std::vector<double>& position, const double &radius, const Material& material)
: Object(position, material),
  radius(radius) {}


double Sphere::get_radius() const {
      return radius;
}


bool Sphere::get_intersection(Intersection& intersection, const Ray& ray) {
    double a = ray.direction.dot(ray.direction);
    double b = 2 * ray.direction.dot(ray.origin - this->get_position());
    double c = (ray.origin - this->get_position()).dot(ray.origin - this->get_position()) - (this->radius * this->radius);
    double det = (b * b) - (4 * a * c);

    if (det == 0) {
        double t = -b / (2 * a);

        if (t > 0) {
            Eigen::Vector3d hit_point = ray.origin + (t * ray.direction);
            Eigen::Vector3d normal = (hit_point - this->get_position()).normalized();
            intersection = Intersection(hit_point, normal, this->get_material());
            return true;
        }
    }

    else if (det > 0) {
        double t1 = (- b + sqrt(det)) / (2 * a);
        double t2 = (-b - sqrt(det)) / (2 * a);

        if (0 < t1 && t1 < t2) {
            Eigen::Vector3d hit_point = ray.origin + (t1 * ray.direction);
            Eigen::Vector3d normal = (hit_point - this->get_position()).normalized();
            intersection = Intersection(hit_point, normal, this->get_material());
            return true;
        }

        else if (0 < t2 && t2 < t1) {
            Eigen::Vector3d hit_point = ray.origin + (t2 * ray.direction);
            Eigen::Vector3d normal = (hit_point - this->get_position()).normalized();
            intersection = Intersection(hit_point, normal, this->get_material());
            return true;
        }
    }
    return false;
}

