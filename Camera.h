#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

class Camera {
    public:
        Camera(float fov, float aspect) {
            float theta = fov * M_PI/180; // conversion to radians
            float halfHeight = tan(theta/2);
            float halfWidth = aspect * halfHeight;
            
            lower_left = Vec3(-halfWidth, -halfHeight, -1.0);
            vertical = Vec3(0.0, 2*halfHeight, 0.0);
            horizontal = Vec3(2*halfWidth, 0.0, 0.0);
            origin = Vec3(0.0, 0.0, 0.0);
        }
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