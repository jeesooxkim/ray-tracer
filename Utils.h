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
        testVal = sample.x()*sample.x() + sample.y()*sample.y() + sample.z()*sample.z();
    } while (testVal > 1);

    return sample;
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v,n)*n;
}

#endif // UTILS_H