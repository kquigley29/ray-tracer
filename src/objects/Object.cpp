//
// Created by keane on 03/10/2020.
//
#include "raytracer/objects/Object.h"
#include<iostream>

Object::Object(const Eigen::Vector3d& position, const Material& material)
: position(position),
  material(material) {}


Object::Object(const std::vector<double>& position, const Material& material)
: position(position.data()),
  material(material) {}


Eigen::Vector3d Object::get_position() {
    return position;
}


Material Object::get_material() {
    return this->material;
}


bool Object::get_intersection(Intersection& intersection, const Ray& ray) {
    std::cout << "hello";
    return false;
}