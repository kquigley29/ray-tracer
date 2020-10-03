//
// Created by keane on 03/10/2020.
//
#include <eigen3/Eigen/Eigen>
#include "raytracer/Material.h"


#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H


struct Intersection {
    Eigen::Vector3d hit_point;
    Eigen::Vector3d normal;
    Material material;

    explicit Intersection(Eigen::Vector3d& hit_point, Eigen::Vector3d& normal, Material material)
    : hit_point(hit_point),
      normal(normal),
      material(material) {}
};


#endif //RAYTRACER_INTERSECTION_H
