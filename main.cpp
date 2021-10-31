# include <iostream>
# include <random>
# include <math.h>
# include "Sphere.h"
# include "HitableList.h"
# include "Camera.h"

Vec3 random_in_unit_sphere() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> distribution(-1, 1);
    Vec3 sample;
    float testVal;

    // TODO: i think there's a better structure for this
    do {
        sample = Vec3(distribution(rng), distribution(rng), distribution(rng));
        // reject if not in unit sphere;
        testVal = sample.x()*sample.x() + sample.y()*sample.y() + sample.z()*sample.z();
    } while (testVal > 1);

    return sample;
}

Vec3 color(const Ray& r, Hitable *world) {
    HitRecord rec;

    // 0.001 to solve shadow acne problem at floating point approx - ignore hits near zero
    if (world->hit(r, 0.001, MAXFLOAT, rec)) { 
        Vec3 target = rec.p + rec.normal  + random_in_unit_sphere();
        return 0.5 * color(Ray(rec.p, target-rec.p), world);
    }

    // background gradient color
    Vec3 unit_direction = unit_vector(r.direction()); // convert to -1.0 < t < 1.0
    float t = 0.5*(unit_direction.y() + 1.0); // convert to 0 < t < 1.0
    return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0); // lerp of white and blue
}

int main() {
    // say this is a 200x100 image (w x h)
    int nx = 200; 
    int ny = 100;
    int ns = 50;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // set camera
    Camera cam;

    int listSize = 2;
    Hitable* list[listSize];

    list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
    list[1] = new Sphere(Vec3(0,-100.5, -1), 100);
    Hitable *world = new HitableList(list, listSize);

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
                total += color(r, world); // shooting the ray to retrieve color
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
}