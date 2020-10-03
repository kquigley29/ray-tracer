//
// Created by keane on 03/10/2020.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include<raytracer/Camera.h>
#include<raytracer/Light.h>
#include<raytracer/objects/Object.h>
#include "Eigen/Eigen";
#include "opencv2/opencv.hpp"

class Scene {
public:
    Scene(Camera& camera, std::vector<Light*> lights, std::vector<Object*> objects);
    cv::Mat render();
private:
    Camera camera;
    std::vector<Light*> lights;
    std::vector<Object*> objects;
};


#endif //RAYTRACER_SCENE_H
