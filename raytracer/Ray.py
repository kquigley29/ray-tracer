import numpy as np


class Ray:
    def __init__(self, ray_origin: list, direction: list):
        self.ray_origin = np.array(ray_origin)
        self.direction = np.array(direction)
