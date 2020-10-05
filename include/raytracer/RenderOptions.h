//
// Created by angus on 05/10/2020.
//

#ifndef RAYTRACER_RENDEROPTIONS_H
#define RAYTRACER_RENDEROPTIONS_H

struct RenderOptions{
    int dof_samples;
    bool gi;
    int gi_recursion;
    int gi_samples;

    RenderOptions(int dof_samples, bool gi, int gi_recursion, int gi_samples)
    {
        this->dof_samples = dof_samples;
        this->gi = gi;
        this->gi_recursion = gi_recursion;
        this->gi_samples = gi_samples;
    }
};

#endif //RAYTRACER_RENDEROPTIONS_H
