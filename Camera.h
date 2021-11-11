#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

class Camera {
    public:
        Camera(Vec3 lowerLeft = Vec3(-2, -1, -1), Vec3 xLength = Vec3(4, 0, 0), Vec3 yLength = Vec3(0, 2, 0), Vec3 center = Vec3(0, 0, 0)) {
            lower_left = lowerLeft;
            horizontal = xLength;
            vertical = yLength;
            origin = center;
        }
        Ray getRay(float u, float v) {
            return Ray(origin, lower_left + u*horizontal + v*vertical - origin);
        }
        Vec3 lower_left;
        Vec3 horizontal;
        Vec3 vertical;
        Vec3 origin;
};

#endif // CAMERA_H