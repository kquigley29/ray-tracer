import matplotlib.pyplot as plt
from camera import Camera
from light import Light
from objects import Sphere
from scene import Scene


def main():
    res = 200
    camera = Camera([0, 0, 5], [0, 0, -1], 0.5, (res, res))
    lights = [Light([0, 2, 11], [100, 100, 100])]
    spheres = [Sphere([0, 0, 0], 2)]
    scene = Scene(camera, lights, spheres)
    image = scene.render()
    plt.imshow(image)
    plt.show()
    print(camera.generate_ray(100,100).direction)


if __name__ == "__main__":
    main()
