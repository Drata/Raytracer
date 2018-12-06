#ifndef METALH
#define METALH

#include "material.h"

class metal : public material {
    public:
        metal(const vec3 &albedo, float fuzz) : m_albedo(albedo), m_fuzz(fuzz) {}

        virtual bool scatter (const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.point, reflected + m_fuzz * random_in_unit_sphere());
            attenuation = m_albedo;
            return (dot(scattered.direction(), rec.normal) > 0 );
        }

        float m_fuzz;
        vec3 m_albedo;
};

#endif