#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Ray.h"
#include "Material.h"

class Lambertian: public Material {
    public:
        Lambertian(const Vec3& a) {
            albedo = a;
        }
        virtual bool scatter(const Ray& ray, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
            Vec3 target = rec.p + rec.normal + random_in_unit_sphere();
            scattered = Ray(rec.p, target-rec.p);
            attenuation = albedo;
            return true;
        }

        Vec3 albedo;
};

#endif // LAMBERTIAN_H