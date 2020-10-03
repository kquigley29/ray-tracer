//
// Created by angus on 03/10/2020.
//

#include "raytracer/PointLight.h"

PointLight::PointLight(Vector3d position, Vector3d intensity) : Light(intensity){
    this->position = position;
    this->intensity = intensity;
}

Vector3d PointLight::calculate_lighting() {}

