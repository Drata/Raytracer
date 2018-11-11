#include <iostream>
#include "vec3.h"
#include "ray.h"

float hit_sphere(const vec3& center, float radius, const ray &r) {
  // vector from origin to center of sphere
  vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = 2.0 * dot(oc, r.direction());
  float c = dot(oc, oc) - radius * radius;
  float discriminant = b * b - 4 * a * c;

  float t;

  if (discriminant < 0) {
    
    return -1.0;
  } else {
    // solution to the second grade ecuation that tell us where in the sphere
    //    the ray is going to hit.
    t = (-b - sqrt(discriminant)) / (2.0 * a);
    return t;
  }
  
}

vec3 color(const ray& r) {
  // sphere at -1 on z axis of radius 0.5
  //      we get the point where the sphere.
  float t = hit_sphere(vec3(0, 0, -1), 0.5, r);

  if(t > 0.0) {
    vec3 N = unit_vector(r.point_at_parameter(t) -  vec3(0, 0, -1));
    return 0.5 * vec3(N.x()+1, N.y()+1, N.z()+1);
  }

  // makes direction unit_vector -1.0 < y 1.0
  vec3 unit_direction = unit_vector(r.direction());

  // 0.0 < t < 1.0
  t = 0.5 * (unit_direction.y() + 1.0);
  // linear interpolation of color between white and blue
  return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
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

  // main loop
  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      // normalizes coordinates
      float u = float(i) / float(nx);
      float v = float(j) / float(ny);

      // creates ray
      ray r(origin, lower_left_corner + u * horizontal + v * vertical);
      vec3 col = color(r);

      // gets color components
      int ir = int(255.99*col[0]);
      int ig = int(255.99*col[1]);
      int ib = int(255.99*col[2]);

      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
