#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H


#include <vector>
#include <eigen3/Eigen/Eigen>
#include "raytracer/Ray.h"
#include "raytracer/Material.h"
#include "raytracer/Intersection.h"


class Object
{
public:
    explicit Object(const Eigen::Vector3d& position, const Material&  material);

    Eigen::Vector3d get_position() const;

    Material get_material() const;

    virtual bool get_intersection(Intersection& intersection, const Ray& ray);

    static Object* parse(const std::vector<std::string>& options);

protected:
    Eigen::Vector3d position;
    Material material;
};


#endif //RAYTRACER_OBJECT_H
