#ifndef RAYTRACER_PARSER_H
#define RAYTRACER_PARSER_H

#include <string>
#include <Eigen/Eigen>
#include "raytracer/Scene.h"


std::string get_option_name(const std::string &option);


std::string get_option_value(const std::string &option);


double get_option_value_double(const std::string &option);


Eigen::Vector3d get_option_value_vector(const std::string &option);


std::vector<std::vector<std::string>> read_cfg(char *filename);


Scene generate_scene(char *filename);


#endif //RAY_TRACER_RAYTRACER_H
