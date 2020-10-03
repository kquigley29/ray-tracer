import numpy as np
from ..utils import normalise
from ..Intersection import Intersection
from ..Material import Material
from ..Ray import Ray
from .Object import Object


class Plane(Object):
    def __init__(self, position: [float], normal: [float], material: Material):
        super().__init__(position, material)
        self.normal = normalise(np.array(normal))

    def get_intersection(self, ray: Ray):
        numerator = np.dot(self.normal, (self.position - ray.ray_origin))
        denominator = np.dot(self.normal, ray.direction)

        if denominator == 0:
            return None

        t = numerator / denominator
        hit_point = ray.ray_origin + t * ray.direction

        return Intersection(hit_point, self.normal, self.material)
