#pragma once
#include "Point3D.h"
#include <vector>

// Class representing an orbit in 3D space, derived from Point3D

class GEOMETRY_API Orbit : public Point3D
{
public:
	Orbit();
	Orbit(Point3D gCenter, float gRadius);
	~Orbit();

public:

	void drawCircle(std::vector<float>& mVertices, std::vector<float>& mColors, float cx, float cy, float radius, int segments); //orbit drawing
	void drawSphere(std::vector<float>& mVertices, std::vector<float>& mColors, float cx, float cy, float radius, Point3D sphereColor); //sphere drawing

private:
	std::vector<Point3D> mPoints;
	float radius;
	Point3D center;
	int sSegments = 600;
	Point3D color;

};