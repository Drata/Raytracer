#ifndef METALH
#define METALH

#include "material.h"

class metal : public material {
    public:
        metal(const vec3 &albedo) : m_albedo(albedo) {}

        virtual bool scatter (const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.point, reflected);
            attenuation = m_albedo;
            return (dot(scattered.direction(), rec.normal) > 0 );
        }

        vec3 m_albedo;
};

#endif