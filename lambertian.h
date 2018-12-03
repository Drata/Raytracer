#ifndef LAMBERTIANH
#define LAMBERTIANH

#include "material.h"

class lambertian : public material {
    public:
        lambertian(const vec3 &albedo) : m_albedo(albedo) {}
        virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
            // punto aleatorio de la esfera tangente al punto de interescción
            vec3 target = rec.point + rec.normal + random_in_unit_sphere();
            
            // el nuevo rayo rebotado va del punto de interseccion al punto aleatorio
            scattered = ray(rec.point, target - rec.point);

            attenuation = m_albedo;
            return true;
        }

        vec3 m_albedo;
};

#endif