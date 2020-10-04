//
// Created by keane on 03/10/2020.
//
#include "raytracer/objects/Object.h"

#ifndef RAYTRACER_DISC_H
#define RAYTRACER_DISC_H

using Eigen::Vector3d;

class Disc : public Object {
public:
    Disc(Vector3d position, Vector3d normal, double radius, Material material);

    bool get_intersection(Intersection &intersection, const Ray &ray) override;

    Vector3d get_normal();
};


#endif //RAYTRACER_DISC_H
