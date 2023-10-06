#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "hit.h"


class sphere : public hittable {
private:
	point3 center;
	double radius;

public:
	sphere(point3 _center, double _radius) : center(_center), radius(_radius) {}

	bool hit(const ray& r, double ray_tmax, double ray_tmin, hit_record& rec) const override {
		vec3 oc = r.get_origin() - center;
		auto a = r.get_direction().length_squared();
		auto half_b = dot(oc, r.get_direction());
		auto c = oc.length_squared() - radius * radius;


		auto discriminant = half_b * half_b - a * c;
		if (discriminant < 0) return false;
		auto sqrtd = sqrt(discriminant);

		//find nearest root that lies in an acceptable range
		auto root = (-half_b - sqrtd) / a;
		if (root <= ray_tmin || ray_tmax <= root) {
			root = (-half_b + sqrtd) / a;
			if (root <= ray_tmin || ray_tmax <= root) {
				return false;
			}
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		vec3 outward_normal = (rec.p - center) / radius;
		rec.set_front_face(r, outward_normal);

		return true;
	}
};

#endif