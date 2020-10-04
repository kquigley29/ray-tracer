#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include <eigen3/Eigen/Eigen>
#include "raytracer/objects/Object.h"
#include "raytracer/Intersection.h"
#include "raytracer/Material.h"
#include "raytracer/Ray.h"


class Sphere: public Object {
public:
    explicit Sphere(const Eigen::Vector3d& position, const double& radius, const Material& material);

    double get_radius() const;

    bool get_intersection(Intersection& intersection, const Ray& ray) override;

private:
    double radius;
};


#endif //RAYTRACER_SPHERE_H
