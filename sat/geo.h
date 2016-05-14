#pragma once

//dealing with geographic coordinates

#include <math.h>
#include <assert.h>

#include "vec.h"

const double RADIUS = 6371.0;

const double PI = 3.1415926535897;

inline double degToRad(double x) {
	return x / 180.0 * PI;
}

//struct for geographic coordinates - longtitude and latitude in radians!
struct geo {
	double lon, lat, rad;
	geo() : lon(0), lat(0), rad(0) {};
	geo(double la, double lo,  double r) :
		 lat( la ), lon( lo ), rad(r)
	{};

};

inline vec3 geoToVec(const geo &g) {
	return vec3(g.rad * cos(g.lat) * cos(g.lon),
				g.rad * cos(g.lat) * sin(g.lon),
				g.rad * sin(g.lat) );
}