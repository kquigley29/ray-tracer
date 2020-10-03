//
// Created by keane on 03/10/2020.
//
#include<raytracer/Camera.h>
#include <iostream>

int main(int argc, char** argv){
    Vector3d pos(0,0,0);
    Vector3d orientation(0, 1, -1);
    std::vector<double> res(2, 200);
    Camera camera(pos, orientation, 2, res);
    std::cout << camera.generate_ray(100,100).direction << "\n";
    return 0;
}