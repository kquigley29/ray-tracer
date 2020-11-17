#include "raytracer/objects/Object.h"


Object::Object(const Eigen::Vector3d& position, const Material& material)
: position(position)
, material(material)
{ }


Eigen::Vector3d Object::get_position() const
{
    return this->position;
}


Material Object::get_material() const
{
    return this->material;
}


bool Object::get_intersection(Intersection& intersection, const Ray& ray)
{
    return false;
}


Object* Object::parse(const std::vector<std::string> &options)
{
    return nullptr;
}