#ifndef HITABLE_H
#define HITABLE_H

# include "Ray.h"

struct HitRecord {
    float t;
    Vec3 p;
    Vec3 normal;
};

class Hitable {
    public:
        virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
};

#endif // HITABLE_H