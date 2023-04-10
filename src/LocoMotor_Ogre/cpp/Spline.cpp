#include "Spline.h"

OgreWrapper::Spline::Spline(bool DebugMode) {
	_spline = new Ogre::SimpleSpline;
	isDebugActive = DebugMode;
}

OgreWrapper::Spline::~Spline() {
	_spline->clear();
	delete _spline;
}

//Adds a new point
void OgreWrapper::Spline::AddPoint(Ogre::Vector3 newPoint) {
	_spline->addPoint(newPoint);
}

//Destroys all Points
void OgreWrapper::Spline::ClearAll() {
	_spline->clear();
}

//Returns a Point from the Spline
Ogre::Vector3 OgreWrapper::Spline::GetPoint(int pointIndex) {
	return _spline->getPoint(pointIndex);
}
//Returns a point based on a TimeIndex, frmo 0-1, representing the whole Spline
Ogre::Vector3 OgreWrapper::Spline::Interpolate(float timeInter) {
	return _spline->interpolate(timeInter);
}
//Recalculate Spline Tangents
void OgreWrapper::Spline::RecalcTangents() {
	_spline->recalcTangents();
}

void OgreWrapper::Spline::SetDebug(bool debugMode) {
	isDebugActive = debugMode;
}
