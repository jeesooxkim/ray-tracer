#ifndef CAMERA_H
#define CAMERA_H

# include "Ray.h"
# include "Utils.h"

class Camera {
    public:
        // fov is top to bottom angle in degrees
        // t0 and t1 are the time period over which the rays are going to be sent out
        Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float fov, float aspect, float aperture, float focalDist, float t0, float t1) {
            time0 = t0;
            time1 = t1;
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
            float time = time0 + drand48()*(time1 - time0); // "random" point in time within time range
            return Ray(origin + offset, lower_left + s*horizontal + t*vertical - origin - offset, time);
        }
        Vec3 lower_left;
        Vec3 horizontal;
        Vec3 vertical;
        Vec3 origin;
        Vec3 u, v, w;

        float time0; // "shutter open time"
        float time1; // "shutter close time"
        float lensRadius;
};

#endif // CAMERA_H