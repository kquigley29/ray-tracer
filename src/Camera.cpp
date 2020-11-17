#include "raytracer/Camera.h"
#include "raytracer/parser.h"


Camera::Camera(const Vector3d& position, const Vector3d& orientation, const double& range, const std::array<double, 2>& resolution)
: position(position)
, orientation(orientation)
, range(range)
, resolution(resolution)
{
    Vector3d i(1,0,0);
    Vector3d j(0,1,0);
    Vector3d k(0,0,1);

    this->width = resolution[0] / resolution[1];
    this->height = 1;
    this->pwidth = 1 / resolution[1];
    this->middle = position + (orientation * range);
    this->left = k.cross(orientation).normalized();
    this->up = orientation.cross(left).normalized();
}


Ray Camera::generate_ray(float x, float y)
{
    Vector3d pix_pos = this->middle - (this->pwidth * x * this->left) - (this->pwidth * y * this->up);
    pix_pos += this->up * this->height / 2 + this->left * this->width / 2;
    Ray ray(this->position, pix_pos - this->position);
    return ray;
}


Eigen::Vector3d Camera::get_position() const
{
    return this->position;
}


std::array<double, 2> Camera::get_resolution() const
{
    return this->resolution;
}


Camera* Camera::parse(const std::vector<std::string> &options)
{
    if (options[0] != "[camera]") return nullptr;

    Eigen::Vector3d position;
    Eigen::Vector3d orientation;
    double range;
    std::array<double, 2> resolution {};
    int requirement_count = 0;
    printf("Parsing [camera]...\n");

    for (int i = 1; i != options.size(); i++)
    {
        std::string option = options[i];
        std::string name = get_option_name(option);

        if (name == "position")
        {
            position = get_option_value_vector(option);
            requirement_count++;
        }
        else if (name == "orientation")
        {
            orientation = get_option_value_vector(option);
            requirement_count++;
        }
        else if (name == "range")
        {
            range = get_option_value_double(option);
            requirement_count++;
        }
        else if (name == "resolution" || name == "res")
        {
            resolution = get_option_value_resolution(option);
            requirement_count++;
        }
        else
        {
            printf("[cfg error] No camera option '%s'.\n\n", name.c_str());
        }
    }
    if (requirement_count >= 4)
    {
        return new Camera(position, orientation, range, resolution);
    }
    printf("[cfg error] Not enough required options were provided for [camera].\n\n");
    return nullptr;
}
