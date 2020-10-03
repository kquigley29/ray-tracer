import matplotlib.pyplot as plt
from python import raytracer as rt


def main():
    res = 500
    camera = rt.Camera([1, 5, 5], [0, -1, -1], 0.5, (res, res))
    lights = [rt.Light([5, 0, 10], [100, 100, 100]),
              rt.Light([-5, 0, 10], [100, 100, 100])]
    objects = [rt.Sphere([-1.5, 0, 0], 2, rt.Material([1.0, 0.4, 0.4])),
               rt.Sphere([1.5, 0, 0], 2, rt.Material([1.0, 0.4, 0.4])),
               rt.Plane([1, 1, 0], [0, 0, 1], rt.Material([1.0, 1.0, 1.0]))]
    scene = rt.Scene(camera, lights, objects)
    image = scene.render()
    plt.imshow(image)
    plt.show()


if __name__ == "__main__":
    main()
