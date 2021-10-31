#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H
#include "Ray.h"

class Lambertian: public Material {
    public:
        Lambertian() {}
        Lambertian(float a) {
            albedo = a;
        }
        virtual bool scatter(const Ray& ray, HitRecord& rec, Vec3& scattered) const;

        float albedo;
};

bool Lambertian::scatter(const Ray& ray, HitRecord& rec, Vec3& scattered) const {

}


#endif // LAMBERTIAN_H