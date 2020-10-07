#include "raytracer/raytracer.h"


int main(int argc, char** argv){
    if (argc != 2) return 1;

    Scene scene = generate_scene(argv[1]);

    cv::Mat image = scene.render_multithreaded();

    cv::imshow("image", image);
    cv::waitKey();

    return 0;
}
