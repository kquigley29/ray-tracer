import numpy as np


class Light:
    def __init__(self, position: list, intensity: list):
        self.position = np.array(position)
        self.intensity = np.array(intensity)
