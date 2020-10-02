from material import Material

class Intersection:
    def __init__(self, hit_point, normal, material : Material):
        self.hit_point = hit_point
        self.normal = normal
        self.material = material
