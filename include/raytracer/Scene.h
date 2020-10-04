#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H


#include <raytracer/Camera.h>
#include<raytracer/lights/Light.h>
#include<raytracer/objects/Object.h>
#include "Eigen/Eigen"
#include "opencv2/opencv.hpp"
#include "thread"
#include "future"


class Scene {
public:
    explicit Scene(const Camera& camera);
    explicit Scene(const Camera& camera, const std::vector<Light*>& lights, const std::vector<Object*>& objects);

    cv::Mat render();
    cv::Mat render_multithreaded(int cores);
    bool get_hit(const Vector3d& origin, const Vector3d& destination);
    void add_object(Object* object);
    void add_light(Light* light);

private:
    Vector3d render_pixel(int x, int y);
    static cv::Mat render_pixels_section(int core, int num_cores, Scene* scene);

    Camera camera;
    std::vector<Light*> lights;
    std::vector<Object*> objects;
};


#endif //RAYTRACER_SCENE_H
