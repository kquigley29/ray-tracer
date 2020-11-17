#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H


#include <eigen3/Eigen/Eigen>
#include "raytracer/Material.h"


struct Intersection
{
    Eigen::Vector3d hit_point;
    Eigen::Vector3d normal;
    Material material;

    explicit Intersection() = default;

    explicit Intersection(const Eigen::Vector3d& hit_point, const Eigen::Vector3d& normal, const Material& material)
    : hit_point(hit_point)
    , normal(normal)
    , material(material)
    { }

    Eigen::Vector3d get_hit_point() const
    {
        return this->hit_point;
    }

    Eigen::Vector3d get_normal() const
    {
        return this->normal;
    }

    Material get_material() const
    {
        return this->material;
    }
};


#endif //RAYTRACER_INTERSECTION_H
