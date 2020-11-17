#include "raytracer/raytracer.h"


int main(int argc, char** argv){
    Scene scene;
    if (argc == 2)
    {
        scene.generate_scene(argv[1]);
        cv::Mat image = scene.render_multithreaded();
        cv::imshow("image", image);
        cv::waitKey();
        return 0;
    }

    if (argc == 3)
    {
        scene.generate_scene(argv[1]);
        cv::Mat image;
        if (strcmp(argv[2], "multi") == 0) image = scene.render_multithreaded();
        else if (strcmp(argv[2], "solo") == 0) image = scene.render();
        cv::imshow("image", image);
        cv::waitKey();
        return 0;
    }
    return 1;
}
