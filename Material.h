#ifndef MATERIAL_H
#define MATERIAL_H

#include "Hitable.h"
#include "Utils.h"

class Material {
    public:
        virtual bool scatter(const Ray& ray, HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
};

#endif // MATERIAL_H 