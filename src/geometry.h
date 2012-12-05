//////////////////////////////////////////////////////////////////////////
// Name: Shane Creighton-Young
// Project: reightracer
// File: geometry.h
//
// Contains: Geometric objects. Points, vectors, lines, spheres, and
// 			 methods for each.
//////////////////////////////////////////////////////////////////////////

#include<sstream>
#include<string>
#include<cmath>

using namespace std;

#ifndef GEOMETRY_H
#define GEOMETRY_H

//////////////////////////////////////////////////////////////////////////
// VECTOR
//

class Vector {
	private:
		double m_x, m_y, m_z;
	
	public:
		Vector(double argx = 0, double argy = 0, double argz = 0) {
			m_x = argx; m_y = argy; m_z = argz;
		}


		double x() { return m_x; }
		double y() { return m_y; }
		double z() { return m_z; }

		
		Vector operator-(Vector u);
		// Dot product of two Vectors
		double operator*(Vector u);
		Vector operator*(double c);
		// magnitude of the vector
		double magnitude();
		Vector normalize();
};

Vector Vector::operator-(Vector u) {
	return Vector(m_x - u.x(), m_y - u.y(), m_z - u.z());
}

double Vector::operator*(Vector u) {
	return m_x * u.x() + m_y * u.y() + m_z * u.z();
}

Vector Vector::operator*(double c) {
	return Vector(c * m_x, c * m_y, c * m_z);
}

double Vector::magnitude() {
	return sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

Vector Vector::normalize() {
	double mag = magnitude();
	double tx = m_x / mag;
	double ty = m_y / mag;
	double tz = m_z / mag;

	return Vector(tx, ty, tz);
}




//////////////////////////////////////////////////////////////////////////
// POINT
//

class Point {
	private:
		double m_x, m_y, m_z;
	
	public:
		Point(double argx = 0, double argy = 0, double argz = 0) {
			m_x = argx; m_y = argy; m_z = argz;
		}


		double x() { return m_x; }
		double y() { return m_y; }
		double z() { return m_z; }

		
		// The subtraction of two points produces a Vector
		Vector operator-(Point b);
};

Vector Point::operator-(Point b) {
	double temp_x = m_x - b.x();
	double temp_y = m_y - b.y();
	double temp_z = m_z - b.z();

	return Vector(temp_x, temp_y, temp_z);
}





//////////////////////////////////////////////////////////////////////////
// SPHERE
//

class Sphere {
	private:
		Point m_center;
		double m_radius;

	
	public:
		Sphere(Point c = Point(0,0,0), double r = 0) {
			m_center = c; m_radius = r;
		}


		Point center() { return m_center; }
		double radius() { return m_radius; }
};




//////////////////////////////////////////////////////////////////////////
// LINE
//

class Line {
	private:
		Point m_origin;
		Vector m_dir;
	

	public:
		Line(Point o = Point(0,0,0), Vector d = Vector(0,0,0)) {
			m_origin = o; m_dir = d;
		}
		Point origin() { return m_origin; }
		Vector dir() { return m_dir; }
		Point point_intersect(Sphere s);
		bool intersect(Sphere s);
};

Point Line::point_intersect(Sphere s) {
	double a = pow(m_dir.x(), 2) + pow(m_dir.y(), 2) + pow(m_dir.z(), 2);
	double b = 2 * m_dir.x() * (m_origin.x() - s.center().x());
	       b+= 2 * m_dir.y() * (m_origin.y() - s.center().y());
		   b+= 2 * m_dir.z() * (m_origin.z() - s.center().z());
	double c = pow(s.center().x(),2) + pow(s.center().y(),2) + pow(s.center().z(),2);
		   c+= pow(m_origin.x(),2) + pow(m_origin.y(),2) + pow(m_origin.z(),2);
		   c-= pow(s.radius(),2);
	
	double t_one = (-b + sqrt(b*b - 4*a*c))/(2*a);
	double t_two = (-b - sqrt(b*b - 4*a*c))/(2*a);

	Point p_one = Point(m_origin.x() + t_one*m_dir.x(), m_origin.y() + t_one*m_dir.y(), m_origin.z() + t_one*m_dir.z());
	Point p_two = Point(m_origin.x() + t_two*m_dir.x(), m_origin.y() + t_two*m_dir.y(), m_origin.z() + t_two*m_dir.z());
	
	double d1 = sqrt(pow(m_origin.x()-p_one.x(),2) + pow(m_origin.y()-p_one.y(),2) + pow(m_origin.z()-p_one.z(),2));
	double d2 = sqrt(pow(m_origin.x()-p_two.x(),2) + pow(m_origin.y()-p_two.y(),2) + pow(m_origin.z()-p_two.z(),2));

	if (d1 <= d2)
		return p_one;
	else
		return p_two;
}

bool Line::intersect(Sphere s) {
	double a = pow(m_dir.x(), 2) + pow(m_dir.y(), 2) + pow(m_dir.z(), 2);
	double b = 2 * m_dir.x() * (m_origin.x() - s.center().x());
	       b+= 2 * m_dir.y() * (m_origin.y() - s.center().y());
		   b+= 2 * m_dir.z() * (m_origin.z() - s.center().z());
	double c = pow(s.center().x(),2) + pow(s.center().y(),2) + pow(s.center().z(),2);
		   c+= pow(m_origin.x(),2) + pow(m_origin.y(),2) + pow(m_origin.z(),2);
		   c-= pow(s.radius(),2);
	
	return (b*b - 4*a*c >= 0);
}




//////////////////////////////////////////////////////////////////////////
// COLOR
//

class Colour { // I'm canadian
	private:
		short m_red;
		short m_green;
		short m_blue;
	
	public:
		Colour(short r = 0, short g = 0, short b = 0) {
			m_red = r; m_green = g; m_blue = b;
		}


		short red() { return m_red; }
		short green() { return m_green; }
		short blue() { return m_blue; }
		Colour operator+(Colour c);

		// convertToString: Converts the colour into string form (ie, "R G B")
		string convertToString();
};

string Colour::convertToString() {
	ostringstream result;
	result << m_red << ' ' << m_green << ' ' << m_blue;
	return result.str();
}

Colour Colour::operator+(Colour c) {
	return Colour(m_red + c.red(), m_green + c.green(), m_blue + c.blue());
}




//////////////////////////////////////////////////////////////////////////
// LIGHT
//

class Light {
	private:
		Point m_position;
		Colour m_diffuse;
		
	public:
		Light(Point p = Point(0,0,0), Colour d = Colour(0,0,0)) {
			m_position = p; m_diffuse = d;
		}


		Point position() { return m_position; }
		Colour diffuse() { return m_diffuse; }
};

#endif
