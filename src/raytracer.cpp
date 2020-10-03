//
// Created by keane on 03/10/2020.
//
#include <iostream>
#include "raytracer/objects/Sphere.h"
#include "raytracer/Ray.h"
#include "raytracer/Material.h"
#include "raytracer/PointLight.h"
#include "opencv2/opencv.hpp"
#include "raytracer/Camera.h"
#include "raytracer/Scene.h"
#include "eigen3/Eigen/Eigen"

using Eigen::Vector3d;

int main(int argc, char** argv){

    Camera camera(Vector3d(0,0,0), Vector3d(0,1,0), 0.5, std::array<double, 2>{1000,800});


    Scene scene(camera, std::vector<Light*>{new PointLight(Vector3d(0,5,10), Vector3d(10000,20000,20000))}, std::vector<Object*>{new Sphere(Vector3d(-0.5,5,0), 1, Material(1,0.5,1)), new Sphere(Vector3d(0.5,5,0), 1, Material(1,1,1))});

    cv::Mat image = scene.render();

    cv::imshow("image", image);
    cv::waitKey();

    return 0;
}