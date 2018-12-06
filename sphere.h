#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
#include "material.h"

class sphere : public hitable {
    public: 
        sphere();
        sphere(vec3 cen, float r, material *mat) : center(cen), radius(r), mat_ptr(mat) {};
        virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
        
        vec3 center;
        float radius;
        material *mat_ptr;
};

bool sphere::hit(const ray &r, float tmin, float tmax, hit_record &rec) const {
    vec3 oc = r.origin() - center;

    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;

    // two's of equation are cancelled
    float discriminant = b * b - a * c;

    if (discriminant > 0) {
        float temp  = (-b - sqrt(discriminant)) / a;

        if (temp < tmax && temp > tmin) {
            rec.t = temp;
            rec.point = r.point_at_parameter(rec.t);
            
            // radius magnitud is equal to (rec.point - center) magnitud so dividing
            //      by it makes the radius a unit vector.
            rec.normal = (rec.point - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }

    return false;
}

#endif