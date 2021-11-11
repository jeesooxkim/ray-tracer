#ifndef SPHERE_H
#define SPHERE_H

# include "Hitable.h"

class Material;

class Sphere: public Hitable {
    public:
        Sphere() {}
        Sphere(Vec3 c, float r, Material* m) {
            center = c;
            radius = r;
            material = m;
        }

        virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const;

        Vec3 center;
        float radius;
        Material* material;
};

bool Sphere::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
    Vec3 oc = r.origin() - center; // vector from offset center of sphere to origin (where the camera ray originates)

    // abc in the quadratic formula
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(r.direction(), oc);
    float c = dot(oc, oc) - radius*radius;

    float discriminant = b*b - 4*a*c; // per quad formula b^2 - 4ac
    if (discriminant > 0) {
        // check solution 1 to see if in range
        float tValue = (-b - sqrt(discriminant)) / (2.0*a);
        if (tValue < tMax && tValue > tMin) {
            rec.t = tValue;
            rec.p = r.point_at_parameter(tValue);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            return true;
        }

        // check solution 2 to see if in range
        tValue = (-b + sqrt(discriminant)) / (2.0*a);
        if (tValue < tMax && tValue > tMin) {
            rec.t = tValue;
            rec.p = r.point_at_parameter(tValue);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = material;
            return true;
        }
    }
    return false; // if negative, then no solution, if 0 then exactly one solution, and if positive, two solutions
}

#endif // SPHERE_H