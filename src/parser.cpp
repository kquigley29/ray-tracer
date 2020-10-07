#include "raytracer/parser.h"
#include "raytracer/Scene.h"
#include "raytracer/Camera.h"
#include "raytracer/objects/Object.h"
#include "raytracer/objects/Sphere.h"
#include "raytracer/objects/Plane.h"
#include "raytracer/objects/Disc.h"
#include "raytracer/lights/Light.h"
#include "raytracer/lights/PointLight.h"
#include <Eigen/Eigen>
#include <iostream>


std::string get_option_name(const std::string &option) {
    std::string::size_type pos = option.find('=');
    return option.substr(0, pos);
}


std::string get_option_value(const std::string &option) {
    std::string::size_type pos = option.find('=');
    return option.substr(pos + 1, option.size() - 1);
}


double get_option_value_double(const std::string &option) {
    std::string value_str = get_option_value(option);
    return std::stod(value_str);
}


Eigen::Vector3d get_option_value_vector(const std::string &option) {
    std::string value_str = get_option_value(option);
    std::vector<double> points(3);
    unsigned int start = value_str.find('(') + 1;
    unsigned int end = value_str.find(')') - 1;

    std::string vector_str = value_str.substr(start, end);

    std::stringstream ss(vector_str);
    std::string token;
    char delimiter = ',';
    int i = 0;

    while (std::getline(ss, token, delimiter)) {
        points[i] = (std::stod(token));
        i++;
    }
    return {points[0], points[1], points[2]};
}


std::vector<std::vector<std::string>> read_cfg(char *filename) {
    std::ifstream file(filename);
    std::string line;
    int line_number = 0;

    std::vector<std::string> part;
    std::vector<std::vector<std::string>> parts;

    while (std::getline(file, line)) {
        line_number++;

        switch (line[0]) {
            case '[':
            case '-':
                part.push_back(line);
                break;

            case '#':
                break;

            case '\0':
                parts.push_back(part);
                part = std::vector<std::string>();
                break;

            default:
                std::cout << "[cfg error] Failed to parse line " << line_number << ".\n\n";
        }
    }
    parts.push_back(part);
    return parts;
}


Camera *parse_camera(const std::vector<std::string>& part) {
    Eigen::Vector3d position;
    Eigen::Vector3d orientation;
    double range;
    double width;
    double height;
    int requirement_count = 0;

    for (const auto &option: part) {
        std::string name = get_option_name(option);

        if (name == "[camera]") {
            std::cout << "[cfg info] Adding camera...\n";
        }
        else if (name == "-position") {
            position = get_option_value_vector(option);
            requirement_count++;
        }
        else if (name == "-orientation") {
            orientation = get_option_value_vector(option);
            requirement_count++;
        }
        else if (name == "-range") {
            range = get_option_value_double(option);
            requirement_count++;
        }
        else if (name == "-width") {
            width = get_option_value_double(option);
            requirement_count++;
        }
        else if (name == "-height") {
            height = get_option_value_double(option);
            requirement_count++;
        }
        else {
            std::cout << "[cfg error] No camera option for '" << name << "'.\n\n";
        }
    }
    if (requirement_count >= 5) {
        return new Camera(position, orientation, range, std::array<double, 2>{width, height});
    }
    else {
        std::cout << "[cfg error] Not enough required options were provided for Sphere.\n\n";
        return nullptr;
    }
}


PointLight *parse_point_light(const std::vector<std::string> &part) {
    Eigen::Vector3d position;
    Eigen::Vector3d intensity;
    int requirement_count = 0;

    for (const auto &option: part) {
        std::string name = get_option_name(option);

        if (name == "[point_light]") {
            std::cout << "[cfg info] Adding point light...\n";
        }
        else if (name == "-position") {
            position = get_option_value_vector(option);
            requirement_count++;
        }
        else if (name == "-intensity") {
            intensity = get_option_value_vector(option);
            requirement_count++;
        }
        else {
            std::cout << "[cfg error] No point light option for '" << name << "'.\n\n";
        }
    }
    if (requirement_count >= 2) {
        return new PointLight(position, intensity);
    }
    else {
        std::cout << "[cfg error] Not enough required options were provided for Point Light.\n\n";
        return nullptr;
    }
}


Sphere *parse_sphere(const std::vector<std::string> &part) {
    Eigen::Vector3d position;
    double radius;
    Eigen::Vector3d colour;
    int requirement_count = 0;

    for (const auto &option: part) {
        std::string name = get_option_name(option);

        if (name == "[sphere]") {
            std::cout << "[cfg info] Adding sphere...\n";
        }
        else if (name == "-position") {
            position = get_option_value_vector(option);
            requirement_count++;
        }
        else if (name == "-radius") {
            radius = get_option_value_double(option);
            requirement_count++;
        }
        else if (name == "-colour" || name == "-color") {
            colour = get_option_value_vector(option);
            requirement_count++;
        }
        else {
            std::cout << "[cfg error] No sphere option for '" << name << "'.\n\n";
        }
    }
    if (requirement_count >= 3) {
        Material material(colour);
        return new Sphere(position, radius, material);
    }
    else {
        std::cout << "[cfg error] Not enough required options were provided for Sphere.\n\n";
        return nullptr;
    }
}


Plane *parse_plane(const std::vector<std::string> &part) {
    Eigen::Vector3d position;
    Eigen::Vector3d normal;
    Eigen::Vector3d colour;
    int requirement_count = 0;

    for (const auto &option: part) {
        std::string name = get_option_name(option);

        if (name == "[plane]") {
            std::cout << "[cfg info] Adding plane...\n";
        }
        else if (name == "-position") {
            position = get_option_value_vector(option);
            requirement_count++;
        }
        else if (name == "-normal") {
            normal = get_option_value_vector(option);
            requirement_count++;
        }
        else if (name == "-colour" || name == "-color") {
            colour = get_option_value_vector(option);
            requirement_count++;
        }
        else {
            std::cout << "[cfg error] No plane option for '" << name << "'.\n\n";
        }
    }
    if (requirement_count >= 3) {
        Material material(colour);
        return new Plane(position, normal, material);
    }
    else {
        std::cout << "[cfg error] Not enough required options were provided for Plane.\n\n";
        return nullptr;
    }
}


Scene generate_scene(char *filename) {
    std::vector<std::vector<std::string>> parts = read_cfg(filename);
    std::cout << "Number of parts: " << parts.size() << "\n\n";
    Scene scene;
    for (const auto &part: parts) {
        if (part[0] == "[camera]") {
            scene.add_camera(parse_camera(part));
            std::cout << "[cfg info] Camera added to scene.\n\n";
        }
        if (part[0] == "[sphere]") {
            scene.add_object(parse_sphere(part));
            std::cout << "[cfg info] Sphere added to scene.\n\n";
        }
        if (part[0] == "[plane]") {
            scene.add_object(parse_plane(part));
            std::cout << "[cfg info] Plane added.\n\n";
        }
        if (part[0] == "[point_light]") {
            scene.add_light(parse_point_light(part));
            std::cout << "[cfg info] Point Light added.\n\n";
        }
    }
    return scene;
}