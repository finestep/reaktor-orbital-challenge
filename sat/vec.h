#pragma once

#include <math.h>

//basic vector stuff and associated operator overloads - some unused

struct vec3 {
	double x, y, z;
	vec3() : x(0), y(0), z(0) {}
	vec3(const vec3 &b): x(b.x), y(b.y), z(b.z) {}
	vec3(double x, double y, double z):
					x(x), y(y), z(z) {}



	inline double len2() const {
		return x*x + y*y + z*z;
	}

	inline double len() const {
		return sqrt( len2() );
	}

	inline vec3 operator/(const double) const;

	inline vec3 unit() const {
		return (*this) / len();
	}

	inline double dot(const vec3 &b) const {
		return x*b.x + y*b.y + z*b.z;
	}
};


inline void operator*=(vec3 &a, const double b) {
	a.x *= b;
	a.y *= b;
	a.z *= b;
}

inline vec3 operator*(const vec3 &a, const double b) {
	vec3 ret = vec3(a);
	ret *= b;
	return ret;
}
inline vec3 operator*(const double b, const vec3 &a) {
	return a*b;
}

inline vec3 operator-(const vec3 &a) {
	return -1 * a;
}

inline void operator+=(vec3 &a, const vec3 &b) {
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
}

inline void operator-=(vec3 &a, const vec3 &b) {
	a += -b;
}

inline vec3 operator+(const vec3 &a,const vec3 &b) {
	vec3 ret = vec3(a);
	ret += b;
	return ret;
}
inline vec3 operator-(const vec3 &a, const vec3 &b) {
	return a + (-b);
}


inline void operator/=(vec3 &a, const double b) {
	a *= (1 / b);
}
inline void operator/=(const double b, vec3 &a) {
	a /= b;
}

inline vec3 vec3::operator/(const double b) const {
	return *this * (1 / b);
}

