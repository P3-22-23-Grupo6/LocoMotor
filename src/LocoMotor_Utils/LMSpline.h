#pragma once
#ifndef LM_SPLINE
#define LM_SPLINE

#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

namespace Ogre {
	class SimpleSpline;
}
class LMVector3;

namespace LocoMotor {
	class MOTOR_API Spline {
	public:
		Spline(bool DebugMode = false);
		~Spline();
		//Ogre::MovableObject* GetMovObj();

		void AddPoint(const LMVector3& newPoint);
		void ClearAll();
		LMVector3 GetPoint(int pointIndex);
		LMVector3 Interpolate(float timeInter);
		void RecalcTangents();
		void SetDebug(bool debugMode);

	private:
		Ogre::SimpleSpline* _spline;
		bool isDebugActive;
	};
}

#endif
