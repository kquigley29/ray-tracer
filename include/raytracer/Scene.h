//
// Created by keane on 03/10/2020.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include<raytracer/Camera.h>
#include<raytracer/lights/Light.h>
#include<raytracer/objects/Object.h>
#include "Eigen/Eigen"
#include "opencv2/opencv.hpp"
#include "thread"
#include "future"

class Scene {
public:
    Scene(Camera& camera, std::vector<Light*> lights, std::vector<Object*> objects);
    cv::Mat render();
    cv::Mat render_multithreaded(int cores);
    bool get_hit(Vector3d orig, Vector3d dest);
private:
    Vector3d render_pixel(int x, int y);
    static cv::Mat render_pixels_section(int core, int num_cores, Scene* scene);

    Camera camera;
    std::vector<Light*> lights;
    std::vector<Object*> objects;
};


#endif //RAYTRACER_SCENE_H
