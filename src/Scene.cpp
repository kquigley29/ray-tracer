#include "raytracer/Scene.h"


Scene::Scene(Camera &camera,const RenderOptions& renderOptions,std::vector<Light*> lights, std::vector<Object*> objects)
: camera(camera)
, lights(lights)
, objects(objects)
, options(renderOptions)
{ }


cv::Mat Scene::render() {
    std::array<double, 2> res = this->camera.get_resolution();
    cv::Mat image(res[1], res[0], CV_8UC3, cv::Scalar(0,0,0));

    for(int y = 0; y < res[1]; y++){
        for(int x = 0; x < res[0]; x++){
            Vector3d colour = this->render_pixel(x, y, 4);
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
        threads.push_back(std::async(Scene::render_pixels_section, i, cores, this->options.dof_samples, this->options.gi_recursion,this));
    }
    for(int i = 0; i < cores; i++){
        image += threads[i].get();
    }

    return image;
}


Vector3d Scene::render_pixel(int x, int y, int depth) {
    Ray generated_ray = this->camera.generate_ray(x, y);
    return cast_ray(generated_ray, depth);
}

Vector3d Scene::cast_ray(const Ray &ray, int depth) {
    Vector3d hit(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(),
                 std::numeric_limits<double>::infinity());
    Vector3d final_colour(0, 0, 0);
    Intersection intersection;
    Intersection closestIntersect;

    //check for recustion depth
    if(depth > 0) {
        //set intersect to false, if no intersections it will stay false
        bool intersect = false;
        for (auto obj : this->objects) {
            if (obj->get_intersection(intersection, ray)) {
                intersect = true;
                double temp_dist1 = (intersection.hit_point - this->camera.get_position()).dot(
                        intersection.hit_point - this->camera.get_position());
                double temp_dist2 = (hit - this->camera.get_position()).dot(hit - this->camera.get_position());

                if (temp_dist1 < temp_dist2) {
                    closestIntersect = intersection;
                    hit = intersection.hit_point;
                }
            }
        }
        if(!intersect){
            return Vector3d (0,0,0);
        }
        Vector3d colour(0, 0, 0);

        for (auto light : this->lights) {
            // check if the intersect point is in shadow to the light, this works by checking for a hit
            // between the hit_point + a tiny amount and the light position
            bool is_in_shadow = this->get_hit(
                    closestIntersect.hit_point + (0.000001 * (light->get_position() - closestIntersect.hit_point)),
                    light->get_position()
            );

            if (!is_in_shadow) {
                Vector3d value = light->calculate_lighting(closestIntersect);
                colour += value;
            }
        }

        Vector3d indirect_colour(0, 0, 0);

        if(this->options.gi) {
            double pdf = 1 / (2 * M_PI);
            for (int i = 0; i < this->options.gi_samples; i++) {
                double r1 = fast_rand();
                Vector3d sample_dir = hemiSampleAboveNormal(closestIntersect.normal, closestIntersect.hit_point, r1) -
                                      closestIntersect.hit_point;
                indirect_colour += r1 * this->cast_ray(Ray(closestIntersect.hit_point + sample_dir * 0.00001, sample_dir),depth - 1) / pdf ;
            }
            indirect_colour = indirect_colour / ((double) this->options.gi_samples) + closestIntersect.material.emission;
        }

        Vector3d a = ((colour / M_PI) + (2 * indirect_colour));

        final_colour = Vector3d(a.x() * closestIntersect.material.colour.x(), a.y() * closestIntersect.material.colour.y(),
                         a.z() * closestIntersect.material.colour.z());
        return final_colour;

    }
    else {
        return Vector3d(0,0,0);
    }
}

cv::Mat Scene::render_pixels_section(int core, int num_cores, int samples, int depth,Scene* scene) {
    cv::Mat image(scene->camera.get_resolution()[1],
                  scene->camera.get_resolution()[0],
                  CV_8UC3,
                  cv::Scalar(0,0,0));
    int section_width = scene->camera.get_resolution()[0] / num_cores;

    if(core != num_cores - 1){
        for(int y = 0; y < scene->camera.get_resolution()[1]; y++){
            for(int x = section_width*core; x < section_width*core + section_width; x ++){
                Vector3d colour(0,0,0);
                for(int i = 0; i < samples; i++) {
                    colour += clamp(scene->render_pixel(x, y, depth));
                }
                colour = colour / samples;
                image.at<cv::Vec3b>(cv::Point(x, y)) = cv::Vec3b(colour.x(), colour.y(), colour.z());
            }
        }
    }
    else if(core == num_cores - 1){
        for(int y = 0; y < scene->camera.get_resolution()[1]; y++){
            for(int x = section_width*core; x < scene->camera.get_resolution()[0]; x ++){
                Vector3d colour = clamp(scene->render_pixel(x, y, depth));
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
