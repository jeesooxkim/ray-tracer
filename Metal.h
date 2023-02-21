#ifndef METAL_H
#define METAL_H

#include "Ray.h"
#include "Material.h"

class Metal: public Material {
    public:
        Metal(const Vec3& a, const float f) {
            albedo = a;
            fuzz = f;
        }
        virtual bool scatter(const Ray& ray, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
            Vec3 reflected = reflect(unit_vector(ray.direction()), rec.normal);
            Vec3 fuzzed = reflected + fuzz*random_in_unit_sphere();
            scattered = Ray(rec.p, fuzzed, ray.time());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

        Vec3 albedo;
        float fuzz;
};

#endif // METAL_H