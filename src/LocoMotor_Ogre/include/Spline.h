#pragma once
#include "RenderEntity.h"
#include <OgreSimpleSpline.h>

namespace OgreWrapper {
	class Spline {
	public:
		Spline();
		~Spline();
		//Ogre::MovableObject* GetMovObj();
		
	protected:
		Ogre::SimpleSpline* _spline;
	};
}