import numpy as np
from .utils import normalise, i, j, k
from .Ray import Ray


class Camera:
    def __init__(self, position: [float], orientation: [float], cam_range: float, resolution: tuple):
        self.position = np.array(position)
        self.orientation = normalise(np.array(orientation))
        self.cam_range = cam_range
        self.resolution = resolution
        self.width = resolution[0] / resolution[1]
        self.height = 1
        self.pwidth = 1 / resolution[1]
        self.middle = self.position + (self.orientation * self.cam_range)
        self.left = normalise(np.cross(k, self.orientation))
        if any([np.array_equal(self.orientation, k), np.array_equal(self.orientation, -k)]):
            self.left = -i
        self.up = normalise(np.cross(self.orientation, self.left))

    def generate_ray(self, x: float, y: float):
        pix_pos = self.middle - (self.pwidth * x * self.left) - (self.pwidth * y * self.up)
        pix_pos += self.up * self.height / 2
        pix_pos += self.left * self.width / 2
        dray = normalise(pix_pos - self.position)

        return Ray(list(self.position), list(dray))
