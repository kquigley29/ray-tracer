#ifndef RAYTRACER_PARSER_H
#define RAYTRACER_PARSER_H


#include <string>
#include <eigen3/Eigen/Eigen>


std::string get_option_name(const std::string& option);


std::string get_option_value(const std::string& option);


double get_option_value_double(const std::string& option);


Eigen::Vector3d get_option_value_vector(const std::string& option);


std::array<double, 2> get_option_value_resolution(const std::string& option);


std::vector<std::vector<std::string>> read_cfg(char* filename);


#endif //RAY_TRACER_RAYTRACER_H
