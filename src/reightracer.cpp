//////////////////////////////////////////////////////////////////////////
// Name: Shane Creighton-Young
// Project: reightracer
// File: reightracer.cpp
// 
// Contains: The main program.
// 
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include "geometry.h"

Colour addAmbientLighting() {
	double c_ambient = 0;
	return Colour(c_ambient, c_ambient, c_ambient);
}

Colour addDiffuseLighting(Point p_surface, Vector v_normal, Light light) {
	const double c_diffuse = 0.5;
	Vector v_light = (light.position() - p_surface).normalize();
	v_normal = v_normal.normalize();
	double dot = v_light * v_normal;
	
	//std::cout << "Light vector: " << v_light.x() << " " << v_light.y() << " " << v_light.z() << std::endl;
	//std::cout << "Normal vector: " << v_normal.x() << " " << v_normal.y() << " " << v_normal.z() << std::endl;
	//if (p_surface.z() < -50) std::cout << "Surface point: " << p_surface.x() << " " << p_surface.y() << " " << p_surface.z() << std::endl;
	
	//std::cout << "dot product: " << dot << std::endl;
	//if (dot > 0) std::cout << "pos" << std::endl;
	double red = c_diffuse * dot;
	// std::cout << "red dump: " << red << " * " << light.diffuse().red() << " = ";
	      red *= light.diffuse().red();
	// std::cout <<  red << std::endl;
	double green = c_diffuse * dot;
	      green *= light.diffuse().green();
	double blue = c_diffuse * dot;
	      blue *= light.diffuse().blue();
	
	// std::cout << "colour: " << red << " " << blue << " " << green << std::endl;
	
	//std::cout << std::endl;
	return Colour(red, green, blue);
}

Colour illuminate(Point p_surface, Vector v_normal, Light lights[]) {
	int len = 3;

	Colour point_colour = addAmbientLighting();
	
	// diffuse lighting for each light
	for (int i = 0; i < len; i++) {
		point_colour = point_colour + addDiffuseLighting(p_surface, v_normal, lights[i]);
	}
	
	return point_colour;
}

// boundColour: Colour Int Int -> Colour
// Bounds a colour to be values between the min and max. If less than the
// min, it makes the value the min, and likewise if it's more than the
// max, it makes the value max.
Colour boundColour(Colour col, int min, int max) {
	int tred = col.red();
	int tgreen = col.green();
	int tblue = col.blue();

	if (tred < min)			tred = min;
	else if (tred > max)	tred = max;
	
	if (tgreen < min)		tgreen = min;
	else if (tgreen > max)	tgreen = max;

	if (tblue < min)		tblue = min;
	else if (tblue > max)	tblue = max;

	return Colour(tred,tgreen,tblue);
}

int main() {
	const int height = 200;
	const int width = 200;
	
	ofstream image;
	image.open("out.ppm");
	image << "P3" << '\n' << width << ' ' << height << '\n' << 255 << '\n';
	
	Point camera(0,0,0);
	
	Light lights [3] = { Light(Point(100,100,100), Colour(200,0,0)),
						 Light(Point(100,-100,100), Colour(0,200,0)),
						 Light(Point(100,0,-100), Colour(0,0,200)) };
	
	Colour background;

	Sphere sphere(Point(200,0,0),50);

	Point plane_point;
	Point surface_point;
	
	//std::cout << illuminate(Point(0,0,0),Vector(2,2,2),Light(Point(4,4,4),Colour(2,2,2))).convertToString() << std::endl;
	
	//std::cout << Line(Point(0,0,0),Vector(1,0,0)).intersect(Sphere(Point(10,0,0),2)) << std::endl;
	
	Line ray;
	Vector direction;
	Colour point_colour;
	for (int z = 100; z > -100; z--) {
		for (int y = 100; y > -100; y--) {
			plane_point = Point(100,y,z);
			direction = plane_point - camera;

			ray = Line(camera, direction);

			if (ray.intersect(sphere)) {
				surface_point = ray.point_intersect(sphere);
				point_colour = illuminate(surface_point, surface_point - sphere.center(), lights);
				point_colour = boundColour(point_colour, 0, 255);
				image << point_colour.convertToString() << ' ';
				//image << "255 255 255 ";
			}
			else {
				image << background.convertToString() << ' ';
			}
		}
		image << '\n';
	}

	image.close();

	return 0;
}
