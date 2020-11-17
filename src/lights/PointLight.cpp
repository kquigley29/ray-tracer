#include "raytracer/lights/PointLight.h"
#include "raytracer/parser.h"


PointLight::PointLight(const Eigen::Vector3d& position, const Eigen::Vector3d& intensity)
: Light(position, intensity)
{ }


Eigen::Vector3d PointLight::calculate_lighting(Intersection& intersection)
{
    Eigen::Vector3d direction = this->get_position() - intersection.hit_point;
    double dist = direction.norm();
    double cos_theta = direction.dot(intersection.normal) / (dist * intersection.normal.norm());

    if(cos_theta < 0)
    {
        return {0,0,0};
    }

    return cos_theta * (Eigen::Vector3d(this->get_intensity().x() * intersection.material.colour.x(),
                                        this->get_intensity().y() * intersection.material.colour.y(),
                                        this->get_intensity().z() * intersection.material.colour.z())) / (dist * dist);
}


PointLight* PointLight::parse(const std::vector<std::string> &options)
{
    if (options[0] != "[point_light]") return nullptr;

    Eigen::Vector3d position;
    Eigen::Vector3d intensity;
    int requirement_count = 0;
    printf("Parsing [point_light]...\n");

    for (int i = 1; i != options.size(); i++)
    {
        std::string option = options[i];
        std::string name = get_option_name(option);

        if (name == "position")
        {
            position = get_option_value_vector(option);
            requirement_count++;
        }
        else if (name == "intensity")
        {
            intensity = get_option_value_vector(option);
            requirement_count++;
        }
        else
        {
            printf("[cfg error] No point light option '%s'.\n\n", name.c_str());
        }
    }
    if (requirement_count >= 2)
    {
        return new PointLight(position, intensity);
    }
    else
    {
        printf("[cfg error] Not enough required options were provided for Point Light. Part ignored.\n\n");
        return nullptr;
    }
}