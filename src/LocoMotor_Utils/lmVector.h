#pragma once

#define _USE_MATH_DEFINES

#include "OgreVector3.h"
#include "OgreQuaternion.h"
#include "btBulletDynamicsCommon.h"
#include "fmod_common.h"
#include <cmath>
class btVector3;
class btTransform;
class btQuaternion;
//Vector class to be used with LocoMotor

class LMVector3 {


public:
	// Default constructor initializes vector to (0, 0, 0)
	/// @brief Create a new Vector3 with everything Set to 0
	LMVector3();

	// Constructor initializes vector to specified values
	/// @brief Create a new Vector3
	LMVector3(double x, double y, double z);

	// Getter functions
	/// @brief Get the X value of the Vector
	double GetX() const;
	/// @brief Get the Y value of the Vector
	double GetY() const;
	/// @brief Get the Z value of the Vector
	double GetZ() const;

	// Setter functions
	/// @brief Set the X value of the Vector
	void SetX(double x);
	/// @brief Set the Y value of the Vector
	void SetY(double y);
	/// @brief Set the Z value of the Vector
	void SetZ(double z);

	// Equal operators of vectors
	LMVector3 operator=(Ogre::Vector3 v);
	LMVector3 operator=(FMOD_VECTOR v);
	LMVector3 operator=(btVector3 v);
	LMVector3 operator=(btTransform v);

	// Sum operators of vectors
	LMVector3 operator+(const LMVector3& other) const;
	LMVector3 operator+(const btVector3& other) const;
	LMVector3 operator+(const btTransform& other) const;
	LMVector3 operator+(const Ogre::Vector3& other) const;
	LMVector3 operator+(const FMOD_VECTOR& other) const;
	LMVector3 operator+(const double& other) const;

	// Sub operators of vectors
	LMVector3 operator-(const LMVector3& other) const;
	LMVector3 operator-(const btVector3& other) const;
	LMVector3 operator-(const btTransform& other) const;
	LMVector3 operator-(const Ogre::Vector3& other) const;
	LMVector3 operator-(const FMOD_VECTOR& other) const;
	LMVector3 operator-(const double& other) const;

	// Mul operators of vectors
	LMVector3 operator*(const LMVector3& other) const;
	LMVector3 operator*(const btVector3& other) const;
	LMVector3 operator*(const btTransform& other) const;
	LMVector3 operator*(const Ogre::Vector3& other) const;
	LMVector3 operator*(const FMOD_VECTOR& other) const;
	LMVector3 operator*(const double& other) const;

	// Div operators of vectors
	LMVector3 operator/(const LMVector3& other) const;
	LMVector3 operator/(const btVector3& other) const;
	LMVector3 operator/(const btTransform& other) const;
	LMVector3 operator/(const Ogre::Vector3& other) const;
	LMVector3 operator/(const FMOD_VECTOR& other) const;
	LMVector3 operator/(const double& other) const;

	// Type operators between vectors
	operator Ogre::Vector3() const;
	operator btVector3() const;
	operator btTransform() const;
	operator FMOD_VECTOR() const;

	// Dot product
	///	@brief Get the Dot Product of two Vectors
	/// @param other The other Vector
	double Dot(const LMVector3& other) const;

	// Cross product
	///	@brief Get the Cross Product of two Vectors
	/// @param other The other Vector
	LMVector3 Cross(const LMVector3& other) const;

	// Cross product
	///	@brief Get the Cross Product of two Vectors
	/// @param normal The normal Vector
	/// @param other The other Vector
	LMVector3 Cross(const LMVector3& other, const LMVector3& normal) const;

	// Magnitude
	///	@brief Get the Magnitude of a Vector
	double Magnitude() const;

	// Normalize
	///	@brief Normalize a Vector
	void Normalize();

	// Angle
	///	@brief Get the Angle between two Vectors
	/// @param other The other Vector to measure from
	double Angle(const LMVector3& other) const;

	// Angle
	///	@brief Get the Angle between two Vectors
	/// @param other The other Vector to measure from
	/// @param normal The normal Vector
	double Angle(const LMVector3& other, const LMVector3& normal) const;

	// Angle
	///	@brief Get the Angle between two Vectors in degrees
	/// @param other The other Vector to measure from
	/// @param normal The normal Vector
	/// @param axis The axis to measure by
	double Angle(const LMVector3& other, const LMVector3& normal, const LMVector3& axis) const;

	// rotate
	///	@brief Rotate a Vector
	/// @param axis The axis to rotate around
	/// @param angle The angle to rotate (degrees)
	LMVector3 Rotate(const LMVector3& axis, double angle) const;
	



// VECTOR TRANSFORMATIONS BETWEEN LANGUAGES
	/// @brief Converts a Bullet vector to lmVector
	static LMVector3 BulletToLm(const btVector3& bulletVector);
   /// @brief Converts an lmVector to Bullet vector
	static btVector3 LmToBullet(const LMVector3& lmVector);
   /// @brief Converts an Ogre vector to lmVector
	static LMVector3 OgreToLm(const Ogre::Vector3& ogreVector);
   /// @brief Converts an lmVector to an Ogre vector
	static Ogre::Vector3 LmToOgre(const LMVector3& lmVector);
	/// @brief Converts an FMod vector to an lmVector
	static LMVector3 FModToLm(const FMOD_VECTOR& fmVector);
	/// @brief Converts an lmVector to an FMod vector
	static FMOD_VECTOR LmToFMod(const LMVector3& lmVector);
	/// @brief Converts a Bullet transform to lmVector
	static LMVector3 BullTransformToLm(const btTransform& bulletTransform);
	/// @brief Converts an lmVector to a Bullet Transform
	static btTransform LmToBullTransform(const LMVector3& lmVector);


private:
	double _x = 0, _y = 0, _z = 0;


};

//Quaternion class to be used with LocoMotor
class LMQuaternion {


public:
	// Default constructor initializes quaternion to (1, 0, 0, 0)
	/// @brief Create a new Quaternion with everything Set to default
	LMQuaternion();

	// Constructor initializes quaternion to specified values
	/// @brief Create a new Quaternion
	LMQuaternion(double w, double x, double y, double z);

	// Getter functions
	/// @brief Get the W value of the Quaternion
	double GetW() const;
	/// @brief Get the X value of the Quaternion
	double GetX() const;
	/// @brief Get the Y value of the Quaternion
	double GetY() const;
	/// @brief Get the Z value of the Quaternion
	double GetZ() const;

//Setter functions
	/// @brief Set the W value of the Quaternion
	void SetW(double w);
	/// @brief Set the X value of the Quaternion
	void SetX(double x);
	/// @brief Set the Y value of the Quaternion
	void SetY(double y);
	/// @brief Set the Z value of the Quaternion
	void SetZ(double z);

	//Equal operators of quaternions
	LMQuaternion operator=(const LMQuaternion& other);
	LMQuaternion operator=(const btQuaternion& other);
	LMQuaternion operator=(const btTransform& other);
	LMQuaternion operator=(const Ogre::Quaternion& other);

	// Add operators of quaternions
	LMQuaternion operator+(const LMQuaternion& other) const;
	LMQuaternion operator+(const btQuaternion& other) const;
	LMQuaternion operator+(const btTransform& other) const;
	LMQuaternion operator+(const Ogre::Quaternion& other) const;

	// Sub operators of quaternions
	LMQuaternion operator-(const LMQuaternion& other) const;
	LMQuaternion operator-(const btQuaternion& other) const;
	LMQuaternion operator-(const btTransform& other) const;
	LMQuaternion operator-(const Ogre::Quaternion& other) const;
	// Mul operators of quaternions
	LMQuaternion operator*(const LMQuaternion& other) const;
	LMQuaternion operator*(const btQuaternion& other) const;
	LMQuaternion operator*(const btTransform& other) const;
	LMQuaternion operator*(const Ogre::Quaternion& other) const;
	LMQuaternion operator*(double scalar) const;

	// Div operators of quaternions
	LMQuaternion operator/(double scalar) const;


	// Conjugate
	/// @brief Get the Conjugate of a Quaternion
	LMQuaternion Conjugate() const;

	// Magnitude
	/// @brief Get the Magnitude of a Quaternion
	double Magnitude() const;

	// Normalize
	/// @brief Normalize a Quaternion
	void Normalize();

	// Rotate
	/// @brief Rotate a Quaternion
	/// @param axis The Axis to rotate around
	/// @param angle The Angle to rotate by (degrees)
	LMQuaternion Rotate(const LMVector3& axis, double angle) const;

	// Rotate a vector by this quaternion
	/// @brief Rotate a Vector by this Quaternion
	/// @param vector The Vector to be rotated
	LMVector3 Rotate(const LMVector3& vector) const;

	// Up vector from Quaternion
	/// @brief Get the Up Vector from a Quaternion
	LMVector3 Up() const;

	// Right vector from Quaternion
	/// @brief Get the Right Vector from a Quaternion
	LMVector3 Right() const;

	// Forward vector from Quaternion
	/// @brief Get the Forward Vector from a Quaternion
	LMVector3 Forward() const;


// QUATERNION TRANSFORMATIONS BETWEEN LANGUAGES
	/// @brief Converts a Bullet quaternion to LMQuaternion
	static LMQuaternion BulletToLm(const btQuaternion& bulletQuaternion);
	/// @brief Converts an LMQuaternion to Bullet vector
	static btQuaternion LmToBullet(const LMQuaternion& LMQuaternion);
	/// @brief Converts an Ogre quaternion to LMQuaternion
	static LMQuaternion OgreToLm(const Ogre::Quaternion& ogreQuaternion);
	/// @brief Converts an LMQuaternion to an Ogre quaternion
	static Ogre::Quaternion LmToOgre(const LMQuaternion& LMQuaternion);
	/// @brief Converts a Bullet transform to LMQuaternion
	LMQuaternion BullTransformToLm(btTransform bulletTransform);
	/// @brief Converts an LMQuaternion to a Bullet Transform
	btTransform LmToBullTransform(LMQuaternion LMQuaternion);
	/// @brief Converts an lmVector and LMQuaternion to a Bullet Transform
	btTransform LmToBullTransform(LMVector3 lmVector, LMQuaternion LMQuaternion);



private:
	double _w = 0, _x = 0, _y = 0, _z = 0;


};