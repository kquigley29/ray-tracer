#include "raytracer/lights/PointLight.h"


PointLight::PointLight(const Eigen::Vector3d& position, const Eigen::Vector3d& intensity)
: Light(position, intensity)
{ }


Eigen::Vector3d PointLight::calculate_lighting(Intersection& intersection) {
    Eigen::Vector3d direction = this->get_position() - intersection.hit_point;
    double dist = direction.norm();
    double cos_theta = direction.dot(intersection.normal) / (dist * intersection.normal.norm());

    if(cos_theta < 0){
        return {0,0,0};
    }

    return cos_theta * (Eigen::Vector3d(this->get_intensity().x() * intersection.material.colour.x(),
                                        this->get_intensity().y() * intersection.material.colour.y(),
                                        this->get_intensity().z() * intersection.material.colour.z())) / (dist * dist);
}
