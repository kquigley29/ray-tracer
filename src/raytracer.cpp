//
// Created by keane on 03/10/2020.
//

#include <iostream>
#include "raytracer/objects/Sphere.h"
#include "raytracer/objects/Plane.h"
#include "raytracer/objects/Disc.h"
#include "raytracer/Ray.h"
#include "raytracer/Material.h"
#include "raytracer/lights/PointLight.h"
#include "opencv2/opencv.hpp"
#include "raytracer/Camera.h"
#include "raytracer/Scene.h"
#include "eigen3/Eigen/Eigen"
#include <cstdlib>
#include<thread>

using Eigen::Vector3d;

int main(int argc, char** argv){

    int cores = std::thread::hardware_concurrency();

    std::array<double, 2> res{800, 800};
    if(argc == 2){
        res[0] = atof(argv[1]);
        res[1] = atof(argv[1]);
    }
    else if(argc == 3){
        res[0] = atof( argv[1]);
        res[1] = atof(argv[2]);
    }


    Camera camera(Vector3d(0,0,3), Vector3d(0,1,-0.5), 0.7, res);

    std::vector<Light*> lights = {new PointLight(Vector3d(0,-1,4), Vector3d(3000,1000,1000)),new PointLight(Vector3d(0,5,1), Vector3d(500,500,500)), new PointLight(Vector3d(0,5,7), Vector3d(2000,2000,3000))};
    std::vector<Object*> objects = {new Plane(Vector3d(5,5,0), Vector3d(-1,-1,0), Material(0.5,1,0.5)), new Plane(Vector3d(0,0,-2), Vector3d(0,0,1), Material(1,1,1)),new Plane(Vector3d(-3,0,0), Vector3d(1,0,0), Material(1,1,1)), new Plane(Vector3d(0,12,0), Vector3d(0,-1,0), Material(1,1,1)),new Sphere(Vector3d(2.5,5,0), 1, Material(1,1,1)), new Sphere(Vector3d(-2.5,5,0), 1, Material(1,0.5,1)), new Sphere(Vector3d(0,3,0), 1, Material(1,0.5,1)), new Sphere(Vector3d(0,7,0), 1, Material(1,1,0.7))};
//    std::vector<Object*> objects = {(new Disc(Vector3d(0,5,0), Vector3d(-1,-1,0), 2, Material(0.5,1,0.5)))};
    Scene scene(camera, lights, objects);

  //  cv::Mat image = scene.render();

    cv::Mat image = scene.render_multithreaded(cores);

    cv::imshow("image", image);
    cv::waitKey();

    return 0;
}
