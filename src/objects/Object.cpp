//
// Created by keane on 03/10/2020.
//

#include "raytracer/objects/Object.h"

#include <utility>


Object::Object(const Eigen::Vector3d& position, const Material& material)
: position(position),
    material(material) {}


Object::Object(const std::vector<double>& position, Material material)
: position(position),
  material(std::move(material)) {}


Vector3d Object::get_position() {
    return position;
}


Material Object::get_material() {
    return material;
}


Intersection* Object::get_intersection(const Ray& ray) {
    return nullptr;
}