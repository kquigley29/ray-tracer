import matplotlib.pyplot as plt
import raytracer as rt


def main():
    res = 200
    camera = rt.Camera([0, 0, 5], [0, 0, -1], 0.5, (res, res))
    lights = [rt.Light([0, 2, 11], [0, 100, 100])]
    spheres = [rt.Sphere([0, 0, 0], 2, rt.Material([1.0, 0.4, 0.4]))]
    scene = rt.Scene(camera, lights, spheres)
    image = scene.render()
    plt.imshow(image)
    plt.show()


if __name__ == "__main__":
    main()
