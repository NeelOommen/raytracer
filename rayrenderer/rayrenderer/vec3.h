#ifndef VEC3_H
#define VEC3_H

#include <cmath>

using std::sqrt;

class vec3 {
public:
	double e[3];

	vec3() : e{ 0,0,0 } {}
	vec3(double e0, double e1, double e2) : e{ e0,e1,e2 } {}

	double x() { return e[0]; }
	double y() { return e[1]; }
	double z() { return e[2]; }

	//operators
	vec3 operator-() const { return vec3(-e[0],-e[1],-e[2]); }
	double operator[] (int i) const { return e[i]; }
	double& operator[] (int i) { return e[i]; }

	vec3& operator+= (const vec3& v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];

		return *this;
	}

	vec3& operator*= (double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;

		return *this;
	}

	vec3& operator/= (double t) {
		return *this *= 1 / t;
	}

	double length_squared() const {
		return (e[0]*e[0]) + (e[1]*e[1]) + (e[2]*e[2]);
	}

	double length() const {
		return sqrt(length_squared());
	}

};

using point3 = vec3;

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& u) {
	return vec3(t * u.e[0], t * u.e[1], t * u.e[2]);
}

inline vec3 operator*(const vec3& u, double t) {
	return t * u;
}

inline vec3 operator/(vec3 u, double t) {
	return (1 / t) * u;
}

inline double dot(const vec3& u, const vec3& v) {
	return (u.e[0] * v.e[0]) + (u.e[1] * v.e[1]) + (u.e[2] * v.e[2]);
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2], u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}


#endif

