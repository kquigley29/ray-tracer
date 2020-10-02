import matplotlib.pyplot as plt
import raytracer as rt


def main():
    res = 200
    camera = rt.Camera([0, 0, 5], [0, 0, -1], 0.5, (res, res))
    lights = [rt.Light([0, 2, 11], [100, 100, 100])]
    spheres = [rt.Sphere([0, 0, 0], 2)]
    scene = rt.Scene(camera, lights, spheres)
    image = scene.render()
    plt.imshow(image)
    plt.show()
    print(camera.generate_ray(100, 100).direction)


if __name__ == "__main__":
    main()
