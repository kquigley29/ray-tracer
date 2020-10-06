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
#include <Eigen/Eigen>
#include <cstdlib>
#include <thread>


int main(int argc, char** argv){

    unsigned int cores = std::thread::hardware_concurrency();

    std::array<double, 2> res{800, 800};
    if(argc == 2){
        res[0] = atof(argv[1]);
        res[1] = atof(argv[1]);
    }
    else if(argc == 3){
        res[0] = atof( argv[1]);
        res[1] = atof(argv[2]);
    }

    Camera camera(Eigen::Vector3d(0,0,3), Eigen::Vector3d(0,1,-0.5), 0.7, res);
    Scene scene(camera);

    scene.add_light(new PointLight(Eigen::Vector3d(0,-1,4), Eigen::Vector3d(3000,1000,1000)));
    scene.add_light(new PointLight(Eigen::Vector3d(0,5,1),Eigen::Vector3d(500,500,500)));
    scene.add_light(new PointLight(Eigen::Vector3d(0,5,7), Eigen::Vector3d(2000,2000,3000)));

    scene.add_object(new Plane(Eigen::Vector3d(0,0,10), Eigen::Vector3d(0,0,-1), Material(1,0.5,0.5)));
    scene.add_object(new Plane(Eigen::Vector3d(5,5,0), Eigen::Vector3d(-1,-1,0), Material(0.5,1,0.5)));
    scene.add_object(new Plane(Eigen::Vector3d(0,0,-2), Eigen::Vector3d(0,0,1), Material(1,1,1)));
    scene.add_object(new Plane(Eigen::Vector3d(-3,0,0), Eigen::Vector3d(1,0,0), Material(1,1,1)));
    scene.add_object(new Plane(Eigen::Vector3d(0,12,0), Eigen::Vector3d(0,-1,0), Material(1,1,1)));
    scene.add_object(new Sphere(Eigen::Vector3d(2.5,5,0), 1, Material(1,1,1)));
    scene.add_object(new Sphere(Eigen::Vector3d(-2.5,5,0), 1, Material(1,0.5,1)));
    scene.add_object(new Sphere(Eigen::Vector3d(0,3,0), 1, Material(1,0.5,1)));
    scene.add_object(new Sphere(Eigen::Vector3d(0,7,0), 1, Material(1,1,0.7)));


    cv::Mat image = scene.render_multithreaded(cores);

    cv::imshow("image", image);
    cv::waitKey();

    return 0;
}
