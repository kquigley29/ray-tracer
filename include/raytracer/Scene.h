#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include<raytracer/Camera.h>
#include<raytracer/lights/Light.h>
#include<raytracer/objects/Object.h>
#include "Eigen/Eigen"
#include "opencv2/opencv.hpp"
#include "thread"
#include "future"
#include "raytracer/RenderOptions.h"


class Scene {
public:
    Scene(Camera& camera,const RenderOptions& renderOptions,std::vector<Light*> lights, std::vector<Object*> objects);
    cv::Mat render();
    cv::Mat render_multithreaded(int cores);
    bool get_hit(const Vector3d& orig, const Vector3d& dest);

private:
    RenderOptions options;
    Vector3d render_pixel(int x, int y, int depth);
    static cv::Mat render_pixels_section(int core, int num_cores, int samples, int depth, Scene* scene);
    Vector3d cast_ray(const Ray& ray, int depth);
    Camera camera;
    std::vector<Light*> lights;
    std::vector<Object*> objects;
};


#endif //RAYTRACER_SCENE_H
