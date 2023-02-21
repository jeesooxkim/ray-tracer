#ifndef MOVINGSPHERE_H
#define MOVINGSPHERE_H

#include "Hitable.h"

class MovingSphere: public Hitable {
    public: 
        MovingSphere() {}
        MovingSphere(Vec3 c0, Vec3 c1, float t0, float t1, float r, Material *m): center0(c0), center1(c1), time0(t0), time1(t1), radius(r), material(m) {};

        virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const;
        Vec3 center(float time) const;

        Vec3 center0, center1;
        float time0, time1;
        float radius;
        Material *material;
};

// center moves linearly from center0 at time0 to center1 at time1
Vec3 MovingSphere::center(float time) const {
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool MovingSphere::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
    Vec3 oc = r.origin() - center(r.time());
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    
    if (discriminant > 0) {
        // check solution 1 to see if in range
        float tValue = (-b - sqrt(discriminant)) / (2.0*a);
        if (tValue < tMax && tValue > tMin) {
            rec.t = tValue;
            rec.p = r.point_at_parameter(tValue);
            rec.normal = (rec.p - center(r.time())) / radius;
            rec.mat_ptr = material;
            return true;
        }

        // check solution 2 to see if in range
        tValue = (-b + sqrt(discriminant)) / (2.0*a);
        if (tValue < tMax && tValue > tMin) {
            rec.t = tValue;
            rec.p = r.point_at_parameter(tValue);
            rec.normal = (rec.p - center(r.time())) / radius;
            rec.mat_ptr = material;
            return true;
        }
    }
    return false;
}

#endif // MOVINGSPHERE_H