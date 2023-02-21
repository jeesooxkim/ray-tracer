#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Ray.h"
#include "Material.h"

class Dielectric: public Material {
    public:
        Dielectric(const float ri) {
            refIndex = ri;
        }
        virtual bool scatter(const Ray& ray, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
            Vec3 reflected = reflect(ray.direction(), rec.normal);
            attenuation = Vec3(1.0, 1.0, 1.0);
            float indexRatio;
            Vec3 outwardNormal;
            Vec3 refracted;
            float reflectProb;
            float cosine;

            if (dot(ray.direction(), rec.normal) > 0) {
                outwardNormal = -rec.normal;
                indexRatio = refIndex; // divide by index of air -> 1.0
                cosine = refIndex * dot(ray.direction(), rec.normal) / ray.direction().length();
            } else {
                outwardNormal = rec.normal; 
                indexRatio = 1.0/refIndex; // direction is from air into material
                cosine = -dot(ray.direction(), rec.normal) / ray.direction().length();
            }

            if (refract(ray.direction(), outwardNormal, indexRatio, refracted)) {
                reflectProb = schlick(cosine, refIndex);
            } else {
                reflectProb = 1.0;
            }

            if (drand48() < reflectProb) {
                scattered = Ray(rec.p, reflected, ray.time());
            } else {
                scattered = Ray(rec.p, refracted, ray.time());
            }
            return true;
        }

        float refIndex;
};

#endif //DIELECTRIC_H