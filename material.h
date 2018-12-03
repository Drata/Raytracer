#ifndef MATERIALH
#define MATERIALH

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

struct hit_record;

class material {
    public: 
        virtual bool scatter(const ray& r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;       
};

#endif