import numpy as np
from light import Light
from intersection import Intersection


def normalise(v):
    mag = np.linalg.norm(v)
    if mag == 0:
        return v
    return v / mag


def calculate_lighting(light: Light, intersection : Intersection):
    direction = light.position - intersection.hit_point
    dist = np.linalg.norm(direction)
    cos_theta = np.dot(direction, intersection.normal) / (dist * np.linalg.norm(intersection.normal))
    if cos_theta < 0:
        return None
    return cos_theta * (light.intensity * intersection.material.color) / dist ** 2