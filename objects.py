import numpy as np
from utils import normalise
from intersection import Intersection


class Object:
    def __init__(self, position):
        self.position = np.array(position)

    def get_intersection(self, ray):
        return None, None, None


class Sphere(Object):
    def __init__(self, position, radius):
        super().__init__(position)
        self.radius = radius

    def get_intersection(self, ray):
        a = np.dot(ray.direction, ray.direction)
        b = np.dot((2 * ray.direction), (ray.ray_origin - self.position))
        c = np.dot((ray.ray_origin - self.position), (ray.ray_origin - self.position)) - (self.radius ** 2)
        det = b ** 2 - 4 * a * c

        if det == 0:
            t = - b / (2 * a)

            if t > 0:
                hit_point = ray.ray_origin + (ray.direction * t)
                return Intersection(hit_point, normalise(hit_point - self.position))

        elif det > 0:
            t1 = (-b + np.sqrt(det)) / (2 * a)
            t2 = (-b - np.sqrt(det)) / (2 * a)

            if 0 < t1 < t2:
                hit_point = ray.ray_origin + (ray.direction * t1)
                return Intersection(hit_point, normalise(hit_point - self.position))

            elif 0 < t2 < t1:
                hit_point = ray.ray_origin + (ray.direction * t2)
                return Intersection(hit_point, normalise(hit_point - self.position))

        return None
