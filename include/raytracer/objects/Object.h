//
// Created by keane on 03/10/2020.
//
#include <vector>
#include <eigen3/Eigen/Eigen>
#include "raytracer/Ray.h"
#include "raytracer/Material.h"
#include "raytracer/Intersection.h"


#ifndef RAYTRACER_OBJECT_H
#define RAYTRACER_OBJECT_H


class Object {
public:
    explicit Object(const Eigen::Vector3d& position, const Material&  material);
    explicit Object(const std::vector<double>& position, const Material&  material);

    Eigen::Vector3d get_position();
    Material get_material();

    virtual Intersection* get_intersection(const Ray& ray);

protected:
    Eigen::Vector3d position;
    Material material;
};


#endif //RAYTRACER_OBJECT_H
