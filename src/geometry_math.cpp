//////////////////////////////////////////////////////////////////////////
// Name: Shane Creighton-Young 
// Project: reightracer
// File: geometry_math.cpp
//
// Contains: Functions that I use in my raytracer, "reightracer"
//////////////////////////////////////////////////////////////////////////

#include<cmath>
#include "geometry.h"

double distance(Point a, Point b) {
	return sqrt(pow(b.x() - a.x(),2) + pow(b.y() - a.y(),2) + pow(b.z() - a.z(),2));
}

Colour illuminate(Point p_surface, Vector v_normal, Light light) {
	const double c_ambient = 0.5;
	const double c_diffuse = 0.5;

	Vector v_light = (p_surface - light.position()).normalize();
	v_normal = v_normal.normalize();

	int red = c_diffuse * (v_light * v_normal);
	red *= light.diffuse().red();

	int green = c_diffuse * (v_light * v_normal);
	green *= light.diffuse().green();

	int blue = c_diffuse * (v_light * v_normal);
	blue *= light.diffuse().blue();

	return Colour(red, green, blue);
}
