import numpy as np
from .Light import Light
from .Intersection import Intersection


i = np.array([1, 0, 0])
j = np.array([0, 1, 0])
k = np.array([0, 0, 1])
zero_v = np.array([0, 0, 0])


def normalise(vector: np.ndarray):
    mag = np.linalg.norm(vector)
    if mag == 0:
        return vector
    return vector / mag


def calculate_lighting(light: Light, intersection: Intersection):
    direction = light.position - intersection.hit_point
    dist = np.linalg.norm(direction)
    cos_theta = np.dot(direction, intersection.normal) / (dist * np.linalg.norm(intersection.normal))
    if cos_theta < 0:
        return None

    return cos_theta * (light.intensity * intersection.material.color) / dist ** 2
