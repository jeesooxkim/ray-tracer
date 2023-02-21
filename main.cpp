# include <iostream>
# include <random>
# include <math.h>
# include <stdlib.h>
# include "Sphere.h"
# include "MovingSphere.h"
# include "HitableList.h"
# include "Lambertian.h"
# include "Metal.h"
# include "Dielectric.h"
# include "Camera.h"

Vec3 color(const Ray& r, Hitable *world, int depth) {
    HitRecord rec;

    // 0.001 to solve shadow acne problem at floating point approx - ignore hits near zero
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        Ray scattered;
        Vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth + 1);
        } else {
            //??
            return Vec3(0,0,0);
        }
    }

    // background gradient color
    Vec3 unit_direction = unit_vector(r.direction()); // convert to -1.0 < t < 1.0
    float t = 0.5*(unit_direction.y() + 1.0); // convert to 0 < t < 1.0
    return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0); // lerp of white and blue
}

Hitable* randomScene() {
    int numObjects = 500;
    Hitable** list = new Hitable*[numObjects+1];
    int i = 1;

    // generate "floor"
    list[0] = new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(Vec3(0.5, 0.5, 0.5)));

    // generate spheres with random material and color
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float chooseMaterial = drand48();
            Vec3 center(a + 0.9*drand48(), 0.2, b + 0.9*drand48());
            if ((center - Vec3(4, 0.2, 0)).length() > 0.9) {
                if (chooseMaterial < 0.8) {
                    list[i++] = new MovingSphere(center, center+Vec3(0, 0.5*drand48(), 0), 0.0, 1.0, 0.2, new Lambertian(Vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
                } else if (chooseMaterial < 0.95) {
                    list[i++] = new Sphere(center, 0.2, new Metal(Vec3(0.5*(1+drand48()), 0.5*(1+drand48()), 0.5*(1+drand48())), 0.5*drand48()));
                } else {
                    list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new Sphere(Vec3(0, 1, 0), 1.0, new Dielectric(1.5));
    list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0, new Lambertian(Vec3(0.4, 0.2, 0.1)));
    list[i++] = new Sphere(Vec3(4, 1, 0), 1.0, new Metal(Vec3(0.7, 0.6, 0.5), 0.0));

    return new HitableList(list, i);
}

int main() {
    // say this is a 200x100 image (w x h)
    int nx = 700; 
    int ny = 500;
    int ns = 50;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // set camera
    Vec3 lookFrom = Vec3(13, 2, 3);
    Vec3 lookAt = Vec3(0, 0, 0);
    Vec3 upDirection = Vec3(0, 1, 0);
    float fov = 20; // angle from top to bottom of viewport
    float focalDist = 10.0;
    float aperture = 0.0;

    Camera cam(lookFrom, lookAt, upDirection, fov, float(nx)/float(ny), aperture, focalDist, 0.0, 1.0);
    Hitable *world = randomScene();

    // the rows are written out from top to bottom
    for (int j = ny - 1; j >= 0; j--) { // -> 199, 198, 197 ... 0
        // the pixels are written out in rows with pixels left to right
        for (int i = 0; i < nx; i++) { // -> 0, 1, 2 ... 99
            Vec3 total = Vec3(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                std::random_device dev;
                std::mt19937 rng(dev());
                std::uniform_real_distribution<> distribution(0, 1); 
                float u = float(i + distribution(rng)) / float(nx); // 0 - 1
                float v = float(j + distribution(rng)) / float(ny); // 1 - 0
                Ray r = cam.getRay(u, v); //ray that goes from origin to this screen
                total += color(r, world, 0); // shooting the ray to retrieve color
            }

            // average color value
            Vec3 col = total / ns;

            // gamma 2 approximation for gamma correction (0-1 values are transformed before being stored as a byte)
            col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            // why the 255.99 instead of 255?
            // well r, g, and b are never 1. the greatest it can be here is 199/200 which multiplies out to 254.71
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    // TODO: write to file, designated by commandline
    // TODO: link to simple GUI

    // call image viewer: feh -g 600x300 --auto-zoom
    // system("feh -g 600x300 --auto-zoom -rSmtime ./output");
}
