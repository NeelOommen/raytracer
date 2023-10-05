#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
private:
	point3 origin;
	vec3 direction;

public:
	ray() {}
	ray(const vec3& orig, const vec3& direc) : origin(orig), direction(direc) {}

	point3 get_origin() const { return origin; }
	vec3 get_direction() const { return direction; }

	point3 at(double t) const {
		return origin + (t * direction);
	}
};

#endif