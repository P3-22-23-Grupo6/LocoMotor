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
namespace LocoMotor {
	class LMVector3;
	class MOTOR_API Spline {

	public:
		/// @brief Creates a ogre Simple Spline
		/// @param DebugMode Sets if it is debug mode or not
		Spline(bool DebugMode = false);
		/// @brief Destructor of the spline
		~Spline();
		/// @brief Adds a new point to the spline
		/// @param newPoint Vector new point to add
		void AddPoint(const LMVector3& newPoint);
		/// @brief Sets if the spline should be auto calculated
		/// @param shouldAutoCalc Bool to set
		void SetAutoCalc(bool shouldAutoCalc);
		/// @brief Clear all the points of the spline
		void ClearAll();
		/// @brief Gets the vector point giving an index
		/// @param pointIndex The index of the point
		/// @return Vector3 of the point
		LMVector3 GetPoint(int pointIndex);
		/// @brief Returns a point based on a TimeInder, from 0-1, representing the whole Spline
		/// @param timeInter 
		/// @return Vector3 of the point
		LMVector3 Interpolate(float timeInter);
		/// @brief Recalculate Spline Tangents
		void RecalcTangents();
		/// @brief Sets the debug mode
		/// @param debugMode
		void SetDebug(bool debugMode);

	private:
		Ogre::SimpleSpline* _spline;
		bool _isDebugActive;
	};
}

#endif
