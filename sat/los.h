#pragma once

//functions for checking line-of-sight

#include <math.h>
#include "geo.h"
#include "vec.h"


////discriminant of x = a*x^2 + b*x + c, real roots iff disc(a,b,c) >= 0
inline double disc(double a, double b, double c) {
	return b*b - 4 * a*c;
}


//first root of x = a*x^2 + b*x + c
inline double root1(double a, double b, double c) {
	return (-b + sqrt( disc(a, b, c) ) ) / (2 * a);
}

//second root of x = a*x^2 + b*x + c
inline double root2(double a, double b, double c) {
	return (-b - sqrt( disc(a, b, c) ) ) / (2 * a);
}


//determines if the line between v and u does not collide with a sphere of radius RADIUS

inline bool isClear(const vec3 &v, const vec3 &u,double rad = RADIUS) {

	vec3 delta = u - v;

	double a = delta.len2();
	double b = 2 * v.dot(delta);
	double c = v.len2() - rad*rad;

	if (disc(a, b, c) >= 0.0) {
		double r1 = root1(a, b, c);
		if (r1 > 0 && r1 < 1) return false;
		double r2 = root2(a, b, c);
		if (r2 > 0 && r2 < 1) return false;
	}

	return true;
}
