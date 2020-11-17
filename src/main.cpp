#include "raytracer/raytracer.h"


void print_help()
{
    printf("[Usage]\n"
                "./trace <cfg file>\n"
                "./trace <cfg file> <multi / solo>\n");
}


int main(int argc, char** argv)
{
    Scene scene;
    cv::namedWindow("image");
    cv::Mat image;
    switch (argc)
    {
        case 2:
            scene.generate_scene(argv[1]);
            image = scene.render_multithreaded();
            cv::imshow("image", image);
            cv::waitKey();
            return 0;

        case 3:
            scene.generate_scene(argv[1]);
            if (strcmp(argv[2], "multi") == 0) image = scene.render_multithreaded();
            else if (strcmp(argv[2], "solo") == 0) image = scene.render();
            cv::imshow("image", image);
            cv::waitKey();
            return 0;

        default:
            print_help();
            return 1;
    }
}
