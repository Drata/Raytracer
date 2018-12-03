#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"

enum {
  LOW = 1,
  MEDIUM = 2, 
  HIGH = 4,
  VERY_HIGH = 10
};

#define DEFINITION MEDIUM 

vec3 color(const ray& r, hitable *world, int depth) {

  hit_record rec;

  if (world->hit(r, 0.001, MAXFLOAT, rec)) {
    ray scattered;
    vec3 attenuation;
    
    if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
        return attenuation*color(scattered, world, depth + 1);
    } else {
        return vec3(0, 0, 0);
    }
  } else {
    // makes direction unit_vector -1.0 < y 1.0
    vec3 unit_direction = unit_vector(r.direction());

    // 0.0 < t < 1.0
    float t = 0.5 * (unit_direction.y() + 1.0);
    // linear interpolation of color between white and blue
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

int main() {
  int nx = 200 * DEFINITION;
  int ny = 100 * DEFINITION;
  int ns = 100 * DEFINITION;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  // creates the objects of the world
  hitable *objects[7];

  // creates two spheres
  objects[0] = new sphere(vec3(0, 0, -1), 0.5, new metal(vec3(1.0, 1.0, 1.0)));
  objects[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
  objects[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
  objects[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8)));
  objects[4] = new sphere(vec3(0.3+0.5, -0.2, -0.5), 0.3, new lambertian(vec3(0.7, 0.2, 0.9)));
  objects[5] = new sphere(vec3(0.7+0.5, -0.2, -0.3), 0.3, new lambertian(vec3(0.4, 0.9, 0.0)));
  objects[6] = new sphere(vec3(0, -0.2, -1), 0.3, new lambertian(vec3(0.4, 1.0, 0.1)));

  hitable *world = new hitable_list(objects, 7);

  // camera
  camera cam;

  // main loop
  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(0, 0, 0);
      
      // antialiasing
      for (int s=0; s < ns; s++) {
        // generate random samples for each pixel
        float u = float(i + drand48()) / float(nx);
        float v = float(j + drand48()) / float(ny);

        // adds up the colors of the samples
        ray r = cam.get_ray(u, v);
        col += color(r, world, 0);
      }

      // founds the average of the color for that pixel
      col /= float(ns);

      // gamma correction
      col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
      
      // gets color components
      int ir = int(255.99*col[0]);
      int ig = int(255.99*col[1]);
      int ib = int(255.99*col[2]);

      // prints rgb value to svg
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
