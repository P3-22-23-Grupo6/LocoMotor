#pragma once

#include "OgreVector3.h"
#include "OgreQuaternion.h"
#include "btBulletDynamicsCommon.h"
#include "fmod_common.h"

//Vector class to be used with LocoMotor
class LMVector3 {


public:
	// Default constructor initializes vector to (0, 0, 0)
	/// @brief Create a new Vector3 with everything Set to 0
	LMVector3 ();

	// Constructor initializes vector to specified values
	/// @brief Create a new Vector3
	LMVector3 (double x, double y, double z);

	// Getter functions
	double GetX () const;
	double GetY () const;
	double GetZ () const;

	// Setter functions
	void SetX (double x);
	void SetY (double y);
	void SetZ (double z);

	// Vector addition
	LMVector3 operator+(const LMVector3& other) const;

// Vector subtraction
	LMVector3 operator-(const LMVector3& other) const;

	// Scalar multiplication
	LMVector3 operator*(double scalar) const;

	// Scalar division
	LMVector3 operator/(double scalar) const;

	LMVector3 operator= (btVector3 bulletVector);

	btVector3 operator= (LMVector3 lmVector);

	LMVector3 operator= (Ogre::Vector3 ogreVector);

	// Dot product
	double Dot (const LMVector3& other) const;

	// Cross product
	LMVector3 Cross (const LMVector3& other) const;

	// Magnitude
	double Magnitude () const;

	// Normalize
	void Normalize ();

// VECTOR TRANSFORMATIONS BETWEEN LANGUAGES
	/// @brief Converts a Bullet vector to lmVector
	static LMVector3 BulletToLm (const btVector3& bulletVector);
   /// @brief Converts an lmVector to Bullet vector
	static btVector3 LmToBullet (const LMVector3& lmVector);
   /// @brief Converts an Ogre vector to lmVector
	static LMVector3 OgreToLm (const Ogre::Vector3& ogreVector);
   /// @brief Converts an lmVector to an Ogre vector
	static Ogre::Vector3 LmToOgre (const LMVector3& lmVector);
	/// @brief Converts an FMod vector to an lmVector
	static LMVector3 FModToLm (const FMOD_VECTOR& fmVector);
	/// @brief Converts an lmVector to an FMod vector
	static FMOD_VECTOR LmToFMod (const LMVector3& lmVector);
	/// @brief Converts a Bullet transform to lmVector
	static LMVector3 BullTransformToLm (const btTransform& bulletTransform);
	/// @brief Converts an lmVector to a Bullet Transform
	static btTransform LmToBullTransform (const LMVector3& lmVector);


private:
	double _x = 0, _y = 0, _z = 0;


};

//Quaternion class to be used with LocoMotor
class LMQuaternion {


public:
	// Default constructor initializes quaternion to (0, 0, 0, 0)
	/// @brief Create a new Quaternion with everything Set to 0
	LMQuaternion ();

	// Constructor initializes quaternion to specified values
	/// @brief Create a new Quaternion
	LMQuaternion (double w, double x, double y, double z);

	// Getter functions
	double GetW () const;
	double GetX () const;
	double GetY () const;
	double GetZ () const;

//Setter functions
	void SetW (double w);
	void SetX (double x);
	void SetY (double y);
	void SetZ (double z);

	// Quaternion addition
	LMQuaternion operator+(const LMQuaternion& other) const;

	// Quaternion subtraction
	LMQuaternion operator-(const LMQuaternion& other) const;

	// Quaternion multiplication
	LMQuaternion operator*(const LMQuaternion& other) const;

	// Scalar multiplication
	LMQuaternion operator*(double scalar) const;

	// Scalar division
	LMQuaternion operator/(double scalar) const;

	// Conjugate
	LMQuaternion Conjugate () const;

	// Magnitude
	double Magnitude () const;

	// Normalize
	void Normalize ();


// QUATERNION TRANSFORMATIONS BETWEEN LANGUAGES
	/// @brief Converts a Bullet quaternion to LMQuaternion
	static LMQuaternion BulletToLm (const btQuaternion& bulletQuaternion);
	/// @brief Converts an LMQuaternion to Bullet vector
	static btQuaternion LmToBullet (const LMQuaternion& LMQuaternion);
	/// @brief Converts an Ogre quaternion to LMQuaternion
	static LMQuaternion OgreToLm (const Ogre::Quaternion& ogreQuaternion);
	/// @brief Converts an LMQuaternion to an Ogre quaternion
	static Ogre::Quaternion LmToOgre (const LMQuaternion& LMQuaternion);
	/// @brief Converts a Bullet transform to LMQuaternion
	LMQuaternion BullTransformToLm (btTransform bulletTransform);
	/// @brief Converts an LMQuaternion to a Bullet Transform
	btTransform LmToBullTransform (LMQuaternion LMQuaternion);
	/// @brief Converts an lmVector and LMQuaternion to a Bullet Transform
	btTransform LmToBullTransform (LMVector3 lmVector, LMQuaternion LMQuaternion);



private:
	double _w = 0, _x = 0, _y = 0, _z = 0;


};