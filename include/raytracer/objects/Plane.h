#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H


#include <eigen3/Eigen/Eigen>
#include "raytracer/objects/Object.h"
#include "raytracer/Intersection.h"
#include "raytracer/Material.h"
#include "raytracer/Ray.h"


class Plane: public Object
{
public:
    explicit Plane(const Eigen::Vector3d& position, const Eigen::Vector3d& normal, const Material& material);

    Eigen::Vector3d get_normal() const;

    bool get_intersection(Intersection& intersection, const Ray& ray) override;

    static Plane* parse(const std::vector<std::string>& options);

private:
    Eigen::Vector3d normal;
};


#endif //RAYTRACER_PLANE_H
