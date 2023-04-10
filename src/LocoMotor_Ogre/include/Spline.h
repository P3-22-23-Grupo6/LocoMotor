#pragma once
#include "RenderEntity.h"
#include <OgreSimpleSpline.h>

namespace OgreWrapper {
	class Spline {
	public:
		Spline(bool DebugMode= false);
		~Spline();
		//Ogre::MovableObject* GetMovObj();
		
		void AddPoint(Ogre::Vector3 newPoint);
		void ClearAll();
		Ogre::Vector3 GetPoint(int pointIndex);
		Ogre::Vector3 Interpolate(float timeInter);
		void RecalcTangents();
		void SetDebug(bool debugMode);

	private:
		Ogre::SimpleSpline* _spline;
		bool isDebugActive;
	};
}