#include "raytracer/lights/Light.h"


Light::Light(const Eigen::Vector3d& intensity)
: intensity(intensity)
{ }


Light::Light(const Eigen::Vector3d& position, const Eigen::Vector3d& intensity)
: position(position)
, intensity(intensity)
{ }


Eigen::Vector3d Light::calculate_lighting(Intersection &intersection) {
    return {0,0,0};
}


Eigen::Vector3d Light::get_position() {
    return this->position;
}


Eigen::Vector3d Light::get_intensity() {
    return this->intensity;
}
