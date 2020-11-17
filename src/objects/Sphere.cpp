#include "raytracer/objects/Sphere.h"
#include "raytracer/parser.h"


Sphere::Sphere(const Eigen::Vector3d& position, const double& radius, const Material& material)
: Object(position, material)
, radius(radius)
{ }


double Sphere::get_radius() const
{
      return radius;
}


bool Sphere::get_intersection(Intersection& intersection, const Ray& ray)
{
    double a = ray.direction.dot(ray.direction);
    double b = 2 * ray.direction.dot(ray.origin - this->get_position());
    double c = (ray.origin - this->get_position()).dot(ray.origin - this->get_position()) - (this->radius * this->radius);

    double det = (b * b) - (4 * a * c);

    if (det == 0)
    {
        double t = -b / (2 * a);

        if (t > 0)
        {
            Eigen::Vector3d hit_point = ray.origin + (t * ray.direction);
            Eigen::Vector3d normal = (hit_point - this->get_position()).normalized();
            intersection = Intersection(hit_point, normal, this->get_material());

            return true;
        }
    }

    else if (det > 0)
    {
        double t1 = (- b + sqrt(det)) / (2 * a);
        double t2 = (-b - sqrt(det)) / (2 * a);

        if (0 < t1 && t1 < t2)
        {
            Eigen::Vector3d hit_point = ray.origin + (t1 * ray.direction);
            Eigen::Vector3d normal = (hit_point - this->get_position()).normalized();
            intersection = Intersection(hit_point, normal, this->get_material());

            return true;
        }

        else if (0 < t2 && t2 < t1)
        {
            Eigen::Vector3d hit_point = ray.origin + (t2 * ray.direction);
            Eigen::Vector3d normal = (hit_point - this->get_position()).normalized();
            intersection = Intersection(hit_point, normal, this->get_material());

            return true;
        }
    }
    return false;
}


Sphere* Sphere::parse(const std::vector<std::string> &options)
{
    if (options[0] != "[sphere]") return nullptr;

    Eigen::Vector3d position;
    double radius;
    Eigen::Vector3d colour;
    int requirement_count = 0;
    printf("Parsing [sphere]...\n");

    for (int i = 1; i != options.size(); i++)
    {
        std::string option = options[i];
        std::string name = get_option_name(option);

        if (name == "position")
        {
            position = get_option_value_vector(option);
            requirement_count++;
        }
        else if (name == "radius")
        {
            radius = get_option_value_double(option);
            requirement_count++;
        }
        else if (name == "colour" || name == "color")
        {
            colour = get_option_value_vector(option);
            requirement_count++;
        }
        else
        {
            printf("[cfg error] No sphere option '%s'.\n\n", name.c_str());
        }
    }
    if (requirement_count >= 3)
    {
        Material material(colour);
        return new Sphere(position, radius, material);
    }
    else
    {
        printf("[cfg error] Not enough required options provided for [sphere]. Part ignored.\n\n");
        return nullptr;
    }
}
