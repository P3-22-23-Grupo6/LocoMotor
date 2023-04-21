#include "LMSpline.h"
#include "LMVector.h"
#include "LmVectorConverter.h"
#include <OgreSimpleSpline.h>

using namespace LocoMotor;

Spline::Spline(bool DebugMode) {
	_spline = new Ogre::SimpleSpline;
	isDebugActive = DebugMode;
}

Spline::~Spline() {
	_spline->clear();
	delete _spline;
}

void LocoMotor::Spline::AddPoint(const LMVector3& newPoint) {
	_spline->addPoint(LmToOgre(newPoint));
}

//Destroys all Points
void Spline::ClearAll() {
	_spline->clear();
}

//Returns a Point from the Spline
LMVector3 Spline::GetPoint(int pointIndex) {
	return OgreToLm(_spline->getPoint(pointIndex));
}
//Returns a point based on a TimeIndex, frmo 0-1, representing the whole Spline
LMVector3 Spline::Interpolate(float timeInter) {
	return OgreToLm(_spline->interpolate(timeInter));
}
//Recalculate Spline Tangents
void Spline::RecalcTangents() {
	_spline->recalcTangents();
}

void Spline::SetDebug(bool debugMode) {
	isDebugActive = debugMode;
}
