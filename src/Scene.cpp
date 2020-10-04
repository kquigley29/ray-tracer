#include "raytracer/Scene.h"


Scene::Scene(Camera &camera, std::vector<Light*> lights, std::vector<Object*> objects)
: camera(camera)
, lights(lights)
, objects(objects)
{ }


cv::Mat Scene::render() {
    std::array<double, 2> res = this->camera.get_resolution();
    cv::Mat image(res[1], res[0], CV_8UC3, cv::Scalar(0,0,0));

    for(int y = 0; y < res[1]; y++){
        for(int x = 0; x < res[0]; x++){
            Vector3d colour = this->render_pixel(x, y);
            image.at<cv::Vec3b>(cv::Point(x, y)) = cv::Vec3b(colour.x(), colour.y(), colour.z());
        }
    }
    return image;
}



cv::Mat Scene::render_multithreaded(int cores) {
    std::array<double, 2> res = this->camera.get_resolution();
    cv::Mat image(res[1], res[0], CV_8UC3, cv::Scalar(0, 0, 0));

    std::vector<std::future<cv::Mat>> threads;
    for(int i = 0; i < cores; i ++){
        threads.push_back(std::async(Scene::render_pixels_section, i, cores, this));
    }
    for(int i = 0; i < cores; i++){
        image += threads[i].get();
    }

    return image;
}


Vector3d Scene::render_pixel(int x, int y) {
    Vector3d hit(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(),
                 std::numeric_limits<double>::infinity());
    Vector3d final_colour(0, 0, 0);

    for (auto obj : this->objects) {
        Ray generated_ray = this->camera.generate_ray(x, y);
        Intersection intersection;
        Vector3d colour(0, 0, 0);

        if (obj->get_intersection(intersection, generated_ray)) {
            double temp_dist1 = (intersection.hit_point - this->camera.get_position()).dot(
                    intersection.hit_point - this->camera.get_position());
            double temp_dist2 = (hit - this->camera.get_position()).dot(hit - this->camera.get_position());

            if (temp_dist1 < temp_dist2) {
                hit = intersection.hit_point;

                for (auto light : this->lights) {
                    // check if the intersect point is in shadow to the light, this works by checking for a hit
                    // between the hit_point + a tiny amount and the light position
                    bool is_in_shadow = this->get_hit(
                            intersection.hit_point + (0.000001 * (light->get_position() - intersection.hit_point)),
                            light->get_position());

                    if (!is_in_shadow) {
                        Vector3d value = light->calculate_lighting(intersection);
                        colour += value;
                    }
                }
                final_colour = clamp(colour);
            }
        }
    }
    return final_colour;
}


cv::Mat Scene::render_pixels_section(int core, int num_cores, Scene* scene) {
    cv::Mat image(scene->camera.get_resolution()[1],
                  scene->camera.get_resolution()[0],
                  CV_8UC3,
                  cv::Scalar(0,0,0));
    int section_width = scene->camera.get_resolution()[0] / num_cores;

    if(core != num_cores - 1){
        for(int y = 0; y < scene->camera.get_resolution()[1]; y++){
            for(int x = section_width*core; x < section_width*core + section_width; x ++){
                Vector3d colour = scene->render_pixel(x, y);
                image.at<cv::Vec3b>(cv::Point(x, y)) = cv::Vec3b(colour.x(), colour.y(), colour.z());
            }
        }
    }
    else if(core == num_cores - 1){
        for(int y = 0; y < scene->camera.get_resolution()[1]; y++){
            for(int x = section_width*core; x < scene->camera.get_resolution()[0]; x ++){
                Vector3d colour = scene->render_pixel(x, y);
                image.at<cv::Vec3b>(cv::Point(x, y)) = cv::Vec3b(colour.x(), colour.y(), colour.z());
            }
        }
    }
    return image;
}


/*
 * gets hits in the scene between  ray and dest
 */
bool Scene::get_hit(const Vector3d& orig, const Vector3d& dest) {
    Intersection intersection;
    bool hit = false;
    for (auto & object : this->objects){

        //if(this->objects[i] != object) {

            if(object->get_intersection(intersection, Ray(orig, dest-orig))){

                //check if the object is between the light and the object
                if((intersection.hit_point - orig).dot(intersection.hit_point - orig) < (dest - orig).dot(dest -orig)) {
                    return true;
                }
            }
        //}
    }
    return hit;
}
