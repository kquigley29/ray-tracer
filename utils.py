import numpy as np
from light import Light


def normalise(v):
    mag = np.linalg.norm(v)
    if mag == 0:
        return v
    return v / mag


def calculate_lighting(light: Light, position: np.array, normal: np.array):
    direction = light.position - position
    dist = np.linalg.norm(direction)
    cos_theta = np.dot(direction, normal) / (dist * np.linalg.norm(normal))
    if cos_theta < 0:
        return None
    return cos_theta * (light.intensity * np.array([1, 1, 1])) / dist ** 2