import numpy as np
from ..Material import Material
from ..Ray import Ray


class Object:
    def __init__(self, position: [float], material: Material):
        self.position = np.array(position)
        self.material = material

    def get_intersection(self, ray: Ray):
        return None
