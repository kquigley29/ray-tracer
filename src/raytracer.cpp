//
// Created by keane on 03/10/2020.
//
#include <iostream>
#include "raytracer/objects/Sphere.h"
#include "raytracer/objects/Plane.h"
#include "raytracer/Ray.h"
#include "raytracer/Material.h"
#include "raytracer/Camera.h"


int main(int argc, char** argv){
    Camera camera(Eigen::Vector3d(0, 0, 0), Eigen::Vector3d(0, 1, 0), 2, {200, 200});
    Sphere sphere(Eigen::Vector3d (0, 5, 0), 2, Material(1, 1, 1));
    Plane plane(Eigen::Vector3d(0, 5, 0), Eigen::Vector3d(0, -1, 0), Material(1, 1, 1));

    Intersection intersection;
    if (plane.get_intersection(intersection, camera.generate_ray(100, 100))) {
        std::cout << intersection.hit_point << "\n";
    }

    return 0;
}