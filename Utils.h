#ifndef UTILS_H
#define UTILS_H

# include <math.h>
# include <random>
# include "Vec3.h"

Vec3 random_in_unit_sphere() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> distribution(-1, 1);
    Vec3 sample;
    float testVal;

    // TODO: i think there's a better structure for this
    do {
        sample = Vec3(distribution(rng), distribution(rng), distribution(rng));
        // reject if not in unit sphere;
    } while (dot(sample, sample) >= 1.0);

    return sample;
}

Vec3 randomInUnitDisk() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> distribution(-1, 1);
    Vec3 p;
    do {
        p = 2.0*Vec3(distribution(rng), distribution(rng), 0) - Vec3(1, 1, 0);
    } while (dot(p,p) >= 1.0);
    return p;
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v,n)*n;
}

bool refract(const Vec3& v, const Vec3& n, const float indexRatio, Vec3& refracted) {
    Vec3 unitVector = unit_vector(v);
    float cosTheta = dot(unitVector, n);
    float discriminant = 1.0 - indexRatio*indexRatio*(1-cosTheta*cosTheta);
    if (discriminant > 0) {
        refracted = indexRatio*(unitVector - n*cosTheta) - n*sqrt(discriminant);
        return true;
    }
    return false;
}

// Christopher Schlick approximation for varying reflectivity depending on incident angle
float schlick(float cosine, float refIndex) {
    float r0 = (1-refIndex) / (1+refIndex);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine), 5);
}

#endif // UTILS_H