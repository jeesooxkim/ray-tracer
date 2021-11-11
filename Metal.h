#ifndef METAL_H
#define METAL_H

#include "Ray.h"
#include "Material.h"

class Metal: public Material {
    public:
        Metal(const Vec3& a) {
            albedo = a;
        }
        virtual bool scatter(const Ray& ray, HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
            Vec3 reflected = reflect(unit_vector(ray.direction()), rec.normal);
            scattered = Ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

        Vec3 albedo;
};

#endif // METAL_H