#include "raytracer/objects/Plane.h"
#include "raytracer/parser.h"


Plane::Plane(const Eigen::Vector3d &position, const Eigen::Vector3d &normal, const Material &material)
: Object(position, material)
, normal(normal)
{ }


Eigen::Vector3d Plane::get_normal() const
{
    return normal;
}


bool Plane::get_intersection(Intersection &intersection, const Ray &ray)
{
    double numerator = this->get_normal().dot(this->get_position() - ray.origin);
    double denominator = this->get_normal().dot(ray.direction);

    if (denominator > 0) return false;

    double t = numerator / denominator;
    Eigen::Vector3d hit_point = ray.origin + (t * ray.direction);
    intersection = Intersection(hit_point, this->get_normal(), this->get_material());

    return true;
}


Plane* Plane::parse(const std::vector<std::string> &options)
{
    if (options[0] != "[plane]") return nullptr;

    Eigen::Vector3d position;
    Eigen::Vector3d normal;
    Eigen::Vector3d colour;
    int requirement_count = 0;
    printf("Parsing [plane]...\n");

    for (int i = 1; i != options.size(); i++)
    {
        std::string option = options[i];
        std::string name = get_option_name(option);

        if (name == "position")
        {
            position = get_option_value_vector(option);
            requirement_count++;
        }
        else if (name == "normal")
        {
            normal = get_option_value_vector(option);
            requirement_count++;
        }
        else if (name == "colour" || name == "color")
        {
            colour = get_option_value_vector(option);
            requirement_count++;
        }
        else
        {
            printf("[cfg error] No plane option '%s'.\n\n", name.c_str());
        }
    }
    if (requirement_count >= 3)
    {
        Material material(colour);
        return new Plane(position, normal, material);
    }
    else
    {
        printf("[cfg error] Not enough required options were provided for [plane]. Part ignored.\n\n");
        return nullptr;
    }
}