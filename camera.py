import numpy as np
from utils import normalise
from ray import Ray


class Camera:
    def __init__(self, position: list, orientation: list, crange: float, resolution: tuple):
        self.position = np.array(position)
        self.orientation = normalise(np.array(orientation))
        self.crange = crange
        self.resolution = resolution
        self.width = resolution[0] / resolution[1]
        self.height = 1
        self.pwidth = 1 / resolution[1]
        self.middle = self.position + (self.orientation * self.crange)
        self.i = np.array([1, 0, 0])
        self.j = np.array([0, 1, 0])
        self.k = np.array([0, 0, 1])
        self.left = normalise(np.cross(self.k, self.orientation))
        if any([np.array_equal(self.orientation, self.k), np.array_equal(self.orientation, -self.k)]):
            self.left = np.array([-1, 0, 0])
        self.up = normalise(np.cross(self.orientation, self.left))

    def generate_ray(self, x, y):
        pix_pos = self.middle - (self.pwidth * x * self.left) - (self.pwidth * y * self.up)
        pix_pos += self.up * self.height / 2
        pix_pos += self.left * self.width / 2
        dray = normalise(pix_pos - self.position)

        return Ray(list(self.position), list(dray))
