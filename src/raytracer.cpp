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
    std::srand(time(NULL));
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

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0,1.0);
    Camera camera(
            Vector3d(0,-10,1.5),
            Vector3d(0,1,0),
            2,
            DOFData(1, 5, 0),
            res
            );

    std::vector<Light*> lights = {
                                  //new PointLight(Vector3d(5,5,7.5), Vector3d(250000,250000,250000))
                                  };

//    std::vector<Object*> objects = {
//            new Plane(Vector3d(0,0,-3), Vector3d(0,0,1), Material(0.1,0.1,0.2)),
//            new Sphere(Vector3d(0,5,-2), 3, Material(0.25,0.15, 0.15)),
//            new Plane(Vector3d(3,0,0), Vector3d(-1,0,0), Material(0.18,0.18,0.18)),
//            new Plane(Vector3d(-3,0,-2), Vector3d(1,0,0), Material(0.1,0.1,0.2)),
//            new Plane(Vector3d(0,0,3), Vector3d(0,0,-1), Material(0.1,0.1,0.2)),
//            new Plane(Vector3d(0,10,0), Vector3d(0,-1,0), Material(0.18,0.18,0.18)),
//
//            };

    std::vector<Object*> objects = {
            new Plane(Vector3d(0,0,-1), Vector3d(0,0,1), Material(0.18,0.18,0.18,0,0,0)),
            new Plane(Vector3d(-3,0,0), Vector3d(1,0,0), Material(0.18,0.05,0.05,0,0,0)),
            new Plane(Vector3d(3,0,0), Vector3d(-1,0,0), Material(0.05,0.18,0.05,0,0,0)),
            new Plane(Vector3d(0,0,4), Vector3d(0,0,-11), Material(0.18,0.18,0.18,1000,1000,1000)),
            new Plane(Vector3d(0,6,0), Vector3d(0,-1,0), Material(0.2,0.2,0.2,0,0,0)),
            new Sphere(Vector3d(0,2,0.5), 1, Material(0.25,0.15, 0.15, 0, 0, 0)),
    };
    Scene scene(camera, RenderOptions(1, true, 3, 20), lights,objects);
    cv::Mat finalImage;
    cv::cvtColor(scene.render_multithreaded(cores), finalImage, cv::COLOR_BGR2RGB);

    cv::imshow("image", finalImage);
    cv::waitKey();

    return 0;
}
