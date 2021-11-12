#ifndef CAMERA_H
#define CAMERA_H

# include "Ray.h"
# include "Utils.h"

class Camera {
    public:
        Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float fov, float aspect, float aperture, float focalDist) {
            lensRadius = aperture / 2;

            float theta = fov * M_PI/180; // conversion to radians
            float halfHeight = tan(theta/2);
            float halfWidth = aspect * halfHeight;

            origin = lookfrom;
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            lower_left = origin - halfWidth*focalDist*u - halfHeight*focalDist*v - focalDist*w;
            vertical = 2*halfHeight*focalDist*v;
            horizontal = 2*halfWidth*focalDist*u;
        }

        Ray getRay(float s, float t) {
            Vec3 lensPoint = lensRadius * randomInUnitDisk();
            Vec3 offset = u*lensPoint.x() + v*lensPoint.y();
            return Ray(origin + offset, lower_left + s*horizontal + t*vertical - origin - offset);
        }
        Vec3 lower_left;
        Vec3 horizontal;
        Vec3 vertical;
        Vec3 origin;
        Vec3 u, v, w;

        float lensRadius;
};

#endif // CAMERA_H