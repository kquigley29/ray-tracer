#ifndef RAYTRACER_DISC_H
#define RAYTRACER_DISC_H


#include "raytracer/objects/Plane.h"


class Disc : public Plane
{
public:
    Disc(const Eigen::Vector3d& position, const Eigen::Vector3d& normal, const double& radius, const Material& material);

    bool get_intersection(Intersection& intersection, const Ray& ray) override;

    double get_radius() const;

private:
    Eigen::Vector3d normal;
    double radius;
};


#endif //RAYTRACER_DISC_H
