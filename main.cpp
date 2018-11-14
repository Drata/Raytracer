#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"

vec3 color(const ray& r, hitable *world) {

  hit_record rec;

  if (world->hit(r, 0.0, MAXFLOAT, rec)) {
    return 0.5 * vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
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
  int nx = 200;
  int ny = 100;
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  // screen vectors
  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);

  // creates the objects of the world
  hitable *objects[2];

  // creates two spheres
  objects[0] = new sphere(vec3(0, 0, -1), 0.5);
  objects[1] = new sphere(vec3(0, -100.5, -1), 100);

  hitable *world = new hitable_list(objects, 2);


  // main loop
  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      // normalizes coordinates
      float u = float(i) / float(nx);
      float v = float(j) / float(ny);

      // creates ray
      ray r(origin, lower_left_corner + u * horizontal + v * vertical);
      
      vec3 point = r.point_at_parameter(2.0);
      vec3 col = color(r, world);

      // gets color components
      int ir = int(255.99*col[0]);
      int ig = int(255.99*col[1]);
      int ib = int(255.99*col[2]);

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
