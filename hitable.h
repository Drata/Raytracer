#ifndef HITABLEH
#define HITABLEH

#include "ray.h"
#include "material.h"

struct hit_record {
    float t;
    vec3 point;
    vec3 normal;
    material *mat_ptr;
};

// abstract hitable class
class hitable {
    public:
        virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
};

#endif 