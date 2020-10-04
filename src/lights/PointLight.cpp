//
// Created by angus on 03/10/2020.
//

#include "raytracer/PointLight.h"

PointLight::PointLight(Vector3d position, Vector3d intensity) : Light(intensity){
    this->position = position;
}

Vector3d PointLight::calculate_lighting(Intersection& intersection) {
    Vector3d direction = this->position - intersection.hit_point;
    double dist = direction.norm();
    double cos_theta = direction.dot(intersection.normal) / (dist * intersection.normal.norm());

    if(cos_theta < 0){
        return Vector3d(0,0,0);
    }

    return cos_theta * (Vector3d(this->intensity.x() * intersection.material.colour.x(), this->intensity.y() * intersection.material.colour.y(), this->intensity.z()*intersection.material.colour.z())) / (dist * dist);
}

