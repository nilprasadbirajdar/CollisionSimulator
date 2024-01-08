#pragma once
#include "OpenGLWindow.h"
#include "Point3D.h"
#include "Orbit.h"
#include<vector>

// Class representing a collision simulator for a solar system
class CollisionSimulator
{
public:
	CollisionSimulator();
	~CollisionSimulator();

public:
	void drawCollisionSystem(std::vector<float>& mVertices, std::vector<float>& mColors);
	void resetPositions();

	const std::vector<float>& getCurrentVertices() const { return mCurrentVertices; }
	const std::vector<float>& getCurrentColors() const { return mCurrentColors; }

private:
	void drawOrbitingDebris1(std::vector<float>& vertices, std::vector<float>& colors); // Draw the first orbiting debris
	void drawOrbitingDebris2(std::vector<float>& vertices, std::vector<float>& colors); // Draw the second orbiting debris

private:
	QVector<float> planetOrbitPeriod;
	double* mSpeedMultiplier;

	// Arrays storing parameters for each debris object
	enum { numDebris = 2};
	float debrisRadius[numDebris] = { 0.2f, 0.3f };
	float debrisDistance[2] = { 9.0f, 10.0f};
	float debrisSpeed[numDebris] = { 0.3f, 1.9f};
	float debrisAngles[numDebris] = { 0.0f , 5.0f};

	float mXCoordinate;
	float mYCoordinate;

	std::vector<Point3D> mSphereColors;

	std::vector<float> mCurrentVertices;
	std::vector<float> mCurrentColors;

	CollisionSimulator* solar;
	Orbit* orbit;
};