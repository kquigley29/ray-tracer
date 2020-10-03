import numpy as np
from ..Material import Material
from ..Ray import Ray
from .Plane import Plane


class Disc(Plane):
    def __init__(self, position: [float], normal: [float], radius: float, material: Material):
        super().__init__(position, normal, material)
        self.radius = radius

    def get_intersection(self, ray: Ray):
        intersection = super().get_intersection(ray)

        if intersection is not None:
            plane_vector = intersection.hit_point - self.position

            if np.linalg.norm(plane_vector) <= self.radius:
                return intersection

        return None
