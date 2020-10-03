import numpy as np


class Light:
    def __init__(self, position: [float], intensity: [float]):
        self.position = np.array(position)
        self.intensity = np.array(intensity)
