#include <raytracer/utils.h>


Eigen::Vector3d clamp(Eigen::Vector3d vec){
    Eigen::Vector3d colour(0,0,0);
    if(vec.x() > 255){
        colour.x() = 255;
    }
    else{
        colour.x() = vec.x();
    }
    if(vec.y() > 255){
        colour.y() = 255;
    }
    else{
        colour.y() = vec.y();
    }
    if(vec.z() > 255){
        colour.z() = 255;
    }
    else{
        colour.z() = vec.z();
    }
    return colour;
}
