//
// Created by angus on 04/10/2020.
//

#include<random>
#include "iostream"
#ifndef RAYTRACER_RANDOMDATA_H
#define RAYTRACER_RANDOMDATA_H

using Eigen::Vector3d;

static unsigned int g_seed;

// Used to seed the generator.
inline void fast_srand(int seed) {
    g_seed = seed;
}

// Compute a pseudorandom integer.
// Output value in range [0, 32767]
inline double fast_rand(void) {
    g_seed = (214013*g_seed+2531011);
    return (double) ((g_seed>>16)&0x7FFF) / 32767;
}

inline void createCoordinateSystem(const Vector3d &N, Vector3d &Nt, Vector3d &Nb)
{
    if (std::fabs(N.x()) > std::fabs(N.y()))
        Nt = Vector3d (N.z(), 0, -N.x()) / sqrtf(N.x() * N.x() + N.z() * N.z());
    else
        Nt = Vector3d (0, -N.z(), N.y()) / sqrtf(N.y() * N.y() + N.z() * N.z());
    Nb = N.cross(Nt);
}

inline Eigen::Vector3d uniformSampleHemisphere(const double &r1, const double &r2)
{
    // cos(theta) = r1 = y
    // cos^2(theta) + sin^2(theta) = 1 -> sin(theta) = srtf(1 - cos^2(theta))
    double sinTheta = sqrt(1 - r1 * r1);
    double phi = M_PI * r2;
    double x = sinTheta * sin(2*phi);
    double y = sinTheta * cos(2*phi);

    return Vector3d(x, y, r1);
}

inline Eigen::Vector3d hemiSampleAboveNormal(Vector3d normal, Vector3d hit, double r1){
    Vector3d left;
    Vector3d forward;
    createCoordinateSystem(normal, left, forward);
    Vector3d sample = uniformSampleHemisphere(r1, fast_rand());
    Vector3d worldSample = (hit + normal * sample.z() + left * sample.x() + forward * sample.y());
    return worldSample;
}


#endif //RAYTRACER_RANDOMDATA_H
