//
// Created by angus on 04/10/2020.
//

#ifndef RAYTRACER_DOFDATA_H
#define RAYTRACER_DOFDATA_H

struct DOFData{
    int sample_count;
    double focal_length;
    double aperture;
    DOFData(int sample_count, double focal_length, double aperture)
    {
        this->sample_count = sample_count;
        this->focal_length = focal_length;
        this->aperture = aperture;
    }
};

#endif //RAYTRACER_DOFDATA_H
