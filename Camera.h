#ifndef CAMERA_H
#define CAMERA_H

# include "Ray.h"
# include "Utils.h"

class Camera {
    public:
        Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float fov, float aspect) {
            float theta = fov * M_PI/180; // conversion to radians
            float halfHeight = tan(theta/2);
            float halfWidth = aspect * halfHeight;

            origin = lookfrom;
            Vec3 w = unit_vector(lookfrom - lookat);
            Vec3 u = unit_vector(cross(vup, w));
            Vec3 v = cross(w, u);

            lower_left = origin - halfWidth*u - halfHeight*v - w;
            vertical = 2*halfHeight*v;
            horizontal = 2*halfWidth*u;
        }

        Ray getRay(float s, float t) {
            return Ray(origin, lower_left + s*horizontal + t*vertical - origin);
        }
        Vec3 lower_left;
        Vec3 horizontal;
        Vec3 vertical;
        Vec3 origin;
};

#endif // CAMERA_H