#include "Spline.h"

OgreWrapper::Spline::Spline() {
	_spline = new Ogre::SimpleSpline;
}

OgreWrapper::Spline::~Spline() {
}

//Ogre::MovableObject* OgreWrapper::Spline::GetMovObj() {
//	return nullptr;// _spline;
//}