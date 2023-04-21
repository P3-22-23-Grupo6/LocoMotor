#pragma once
#ifndef _3D_UNITS
#define _3D_UNITS
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

class LMVector3;
class LMQuaternion;

class MOTOR_API Vector3D {

public:
// Default constructor initializes vector to (0, 0, 0)
/// @brief Create a new Vector3D with everything set to 0
	Vector3D();
	
	// Constructor initializes vector to specified values
	/// @brief Create a new Vector3D with the specified values
	Vector3D(double x, double y, double z);

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

	// Sum operators of vectors
	Vector3D operator+(const Vector3D& other);

	// Sub operators of vectors
	Vector3D operator-(const Vector3D& other);

	// Multiply operators of vectors
	Vector3D operator*(const Vector3D& other);
	
	//Multiply operators of vectors with a double
	Vector3D operator*(const double& other);

	// Divide operators of vectors
	Vector3D operator/(const Vector3D& other);
	
	// Divide operators of vectors with a double
	Vector3D operator/(const double& other);


	//Normalize a vector
	/// @brief Normalize the Vector
	Vector3D Normalize();

	//Magnitude of a vector
	/// @brief Get the Magnitude of the Vector
	double Magnitude();

	//Lerp between two vectors
	/// @brief Lerp between two Vectors
	/// @param other The other Vector to Lerp with
	/// @param t The t value to Lerp with
	Vector3D Lerp(Vector3D& other, double t);

	//Distance between 2 vectors
	/// @brief Get the Distance between two Vectors
	/// @param other The other Vector to get the Distance with
	double Distance(Vector3D& other);

	//Rotate a vector in degrees
	/// @brief Rotate the Vector in Degrees
	/// @param axis The Axis to Rotate the Vector
	/// @param degrees The Degrees to Rotate the Vector
	Vector3D Rotate(Vector3D& axis, double& degrees);

	//Point a vector towards another vector
	/// @brief Point the Vector towards another Vector
	/// @param other The other Vector to Point the Vector towards
	/// @note Remember that this vector will be normalized
	Vector3D PointTowards(Vector3D& other);

	//Cross product of two vectors
	/// @brief Get the Cross Product of two Vectors
	/// @param other The other Vector to get the Cross Product with
	Vector3D Cross(Vector3D& other);
	
	//Dot product of two vectors
	/// @brief Get the Dot Product of two Vectors
	/// @param other The other Vector to get the Dot Product with
	double Dot(Vector3D& other);
	
	
private:
	//Makes it able to convert to LMVector3 for LocoMotor
	operator LMVector3() const;
	
	double _x;
	double _y;
	double _z;
};

class MOTOR_API Quaternion3D {

public:
	// Default constructor initializes quat to (0, 0, 0, 0)
	/// @brief Create a new Quaternion with everything Set to 0
	Quaternion3D();

	// Constructor initializes quat to specified values
	/// @brief Create a new Quaternion
	Quaternion3D(double x, double y, double z, double w);

	// Getter functions
	/// @brief Get the X value of the Quaternion
	double GetX() const;
	/// @brief Get the Y value of the Quaternion
	double GetY() const;
	/// @brief Get the Z value of the Quaternion
	double GetZ() const;
	/// @brief Get the W value of the Quaternion
	double GetW() const;
	
	// Setter functions
	/// @brief Set the X value of the Quaternion
	void SetX(double x);
	/// @brief Set the Y value of the Quaternion
	void SetY(double y);
	/// @brief Set the Z value of the Quaternion
	void SetZ(double z);
	/// @brief Set the W value of the Quaternion
	void SetW(double w);
	
	// Sum operators of quaternions
	Quaternion3D operator+(const Quaternion3D& other);
	
	// Sub operators of quaternions
	Quaternion3D operator-(const Quaternion3D& other);
	
	// Multiply operators of quaternions
	Quaternion3D operator*(const Quaternion3D& other);

	// Multiply operators of quaternions with a double
	Quaternion3D operator*(const double& other);
	
	// Divide operators of quaternions
	Quaternion3D operator/(const Quaternion3D& other);

	// Divide operators of quaternions with a double
	Quaternion3D operator/(const double& other);


	//Normalize a quaternion
	/// @brief Normalize the Quaternion
	Quaternion3D Normalize();

	//Magnitude of a quaternion
	/// @brief Get the Magnitude of the Quaternion
	double Magnitude();
	
	//Conjugate of a quaternion
	/// @brief Get the Conjugate of the Quaternion
	Quaternion3D Conjugate();

	//Quaternion rotation by degrees
	/// @brief Rotate the Quaternion in Degrees
	/// @param axis The Axis to Rotate the Quaternion
	/// @degrees The Degrees to Rotate the Quaternion
	Quaternion3D Rotate(Vector3D& axis, double& degrees);
	
	//Vector rotation with a quaternion
	/// @brief Rotate a Vector with the Quaternion
	/// @param other The Vector to Rotate
	/// @param quat The Quaternion to Rotate with
	Vector3D QuaternionRotate(Vector3D& other, Quaternion3D& quat);

	
private:
	//Makes it able to convert to LMQuaternion for LocoMotor
	operator LMQuaternion() const;
	
	double _x;
	double _y;
	double _z;
	double _w;
	
};
#endif