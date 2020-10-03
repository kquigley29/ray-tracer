//
// Created by keane on 03/10/2020.
//

#include "../include/raytracer/Scene.h"
#include<iostream>

Scene::Scene(Camera &camera, std::vector<Light*> lights, std::vector<Object*> objects)
    : camera(camera), lights(lights), objects(objects){};

cv::Mat Scene::render() {
    std::array<double, 2> res = this->camera.get_resolution();
    cv::Mat image(res[1], res[0], CV_8UC3, cv::Scalar(0,0,0));

    for(int y = 0; y < res[1]; y++){

        for(int x = 0; x < res[0]; x++){
            Vector3d hit(std::numeric_limits<double>().infinity(), std::numeric_limits<double>().infinity(), std::numeric_limits<double>().infinity());

            for( auto obj : this->objects){


                Ray generated_ray = this->camera.generate_ray(x, y);

                Intersection intersection;

                Vector3d colour(0,0,0);

                if(obj->get_intersection(intersection, generated_ray)){

                    double temp_dist1 = (intersection.hit_point - this->camera.position).norm();
                    double temp_dist2 = (hit - this->camera.position).norm();

                    if(temp_dist1 < temp_dist2){

                        hit = intersection.hit_point;

                        for(auto light : this->lights){

                            Vector3d value = light->calculate_lighting(intersection);

                            colour += value;

                        }
                        image.at<cv::Vec3b>(cv::Point(x,y)) = cv::Vec3b(colour.x(), colour.y(), colour.z());

                    }

                }

            }

        }



    }
    return image;
}