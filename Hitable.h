#ifndef HITABLE_H
#define HITABLE_H

# include "Ray.h"

class Material;

struct HitRecord {
    float t;
    Vec3 p;
    Vec3 normal;
    Material *mat_ptr;
};

class Hitable {
    public:
        virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
};

#endif // HITABLE_H