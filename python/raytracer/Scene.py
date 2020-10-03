import numpy as np
from .Camera import Camera
from .Light import Light
from python.raytracer import Object
from .utils import calculate_lighting


class Scene:
    def __init__(self, camera: Camera, lights: [Light], objects: [Object]):
        self.camera = camera
        self.lights = lights
        self.objects = objects

    def render(self):
        res = self.camera.resolution
        image = np.zeros((res[0], res[1], 3))

        for y in range(res[1]):
            for x in range(res[0]):
                hit = np.array([np.inf, np.inf, np.inf])

                for obj in self.objects:
                    generated_ray = self.camera.generate_ray(x, y)
                    intersection = obj.get_intersection(generated_ray)
                    color = np.full(3, 0.)

                    if intersection is not None:
                        temp_dist1 = np.linalg.norm(intersection.hit_point - self.camera.position)
                        temp_dist2 = np.linalg.norm(hit - self.camera.position)
                        if temp_dist1 < temp_dist2:
                            hit = intersection.hit_point

                            for light in self.lights:
                                value = calculate_lighting(light, intersection)

                                if value is not None:
                                    color += value

                            image[y][x] = color

        return image
