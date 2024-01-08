#include "stdafx.h"
#include "CollisionSimulator.h"

CollisionSimulator::CollisionSimulator()
{
	mSphereColors =
	{
	Point3D(1.0, 0.0, 0.0),  // Red
	Point3D(0.0, 1.0, 0.0)  // Green
	};
	mSpeedMultiplier = new double;
	orbit = new Orbit();
	*mSpeedMultiplier = 1.0;

	planetOrbitPeriod = {
		87.97f,
		224.7f,
		365.0f
	};
}

CollisionSimulator::~CollisionSimulator()
{

}

void CollisionSimulator::drawCollisionSystem(std::vector<float>& mVertices, std::vector<float>& mColors)
{
	orbit->drawSphere(mVertices, mColors, 0, 0, 6, mSphereColors[0]);
	orbit->drawCircle(mVertices, mColors, 0, 0, 8, 100);
	orbit->drawCircle(mVertices, mColors, 0, 0, 15, 100);
	drawOrbitingDebris1(mVertices, mColors);
	drawOrbitingDebris2(mVertices, mColors);
}

void CollisionSimulator::drawOrbitingDebris1(std::vector<GLfloat>& mVertices, std::vector<GLfloat>& mColors)
{

		float theta = float(debrisAngles[0]) * 3.1415926f / 180.0f;
		float x = debrisDistance[0] * cosf(theta);
		float y = debrisDistance[0] * sinf(theta);

		orbit->drawSphere(mVertices, mColors, x, y, 0.5, mSphereColors[1]);

		//mXCoordinate = 

		debrisAngles[0] += debrisSpeed[0];

		// Angle Should be 360 degrees	
		if (debrisAngles[0] >= 360.0f) {
			debrisAngles[0] -= 360.0f;
		}
}

void CollisionSimulator::drawOrbitingDebris2(std::vector<GLfloat>& mVertices, std::vector<GLfloat>& mColors)
{

		float theta = float(debrisAngles[1]) * 3.1415926f / 180.0f;
		float x = debrisDistance[1] * cosf(theta);
		float y = debrisDistance[1] * sinf(theta);	

		orbit->drawSphere(mVertices, mColors, x, y, 1, mSphereColors[1]);

		if (debrisDistance[1] <= debrisDistance[0] + 0.5) {
			debrisDistance[1] += 1.0f;
			debrisDistance[0] -= 1.0f;
		}

		debrisAngles[1] += debrisSpeed[1];

		// Angle Should be 360 degrees
		if (debrisAngles[1] >= 360.0f) {
			debrisAngles[1] -= 360.0f;
		}
}

void CollisionSimulator::resetPositions()
{
	
	debrisAngles[0] = 0.0f;
	debrisAngles[1] = 3.0f;
	debrisDistance[0] = 9.0f;
	debrisDistance[1] = 11.0f;
}

