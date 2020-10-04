//
// Created by angus on 03/10/2020.
//

#include "raytracer/lights/Light.h"

Light::Light(Vector3d intensity) {
    this->intensity = intensity;
}

Vector3d Light::calculate_lighting(Intersection &intersection) {
    return Vector3d(0,0,0);
}