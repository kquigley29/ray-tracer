//
// Created by keane on 03/10/2020.
//
#include <iostream>
#include "raytracer/objects/Sphere.h"
#include "raytracer/Ray.h"
#include "raytracer/Material.h"


int main(int argc, char** argv){
    Sphere sphere(Eigen::Vector3d(0, 5, 0), 2, Material(1, 1, 1));
    auto ray_origin = Eigen::Vector3d(0,0,0);
    auto ray_dir = Eigen::Vector3d(0,1,0);
    auto intersect = sphere.get_intersection(Ray(ray_origin, ray_dir));
    std::cout << intersect->hit_point << "\n";
    std::cout << intersect->normal << "\n";
    return 0;
}