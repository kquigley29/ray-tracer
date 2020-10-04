#include "raytracer/objects/Disc.h"


Disc::Disc(const Eigen::Vector3d& position, const Eigen::Vector3d& normal, const double& radius, const Material& material)
: Plane(position, normal, material)
, radius(radius)
{ }


bool Disc::get_intersection(Intersection &intersection, const Ray &ray) {
    if (Plane::get_intersection(intersection, ray)) {
        Eigen::Vector3d plane_vector = intersection.get_hit_point() - this->position;

        return plane_vector.norm() <= this->get_radius();
    }
    return false;
}


double Disc::get_radius() const {
    return this->radius;
}
