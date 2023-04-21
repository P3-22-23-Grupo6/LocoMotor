#define _USE_MATH_DEFINES

#include "LMVector.h"

#include <cmath>
//#include "btBulletDynamicsCommon.h"
//Vector class to be used with LocoMotor

// Default constructor initializes vector to (0, 0, 0)
LMVector3::LMVector3() : _x(0), _y(0), _z(0) {
}

// Constructor initializes vector to specified values
LMVector3::LMVector3(double x, double y, double z) : _x(x), _y(y), _z(z) {
}

// Getter functions
// Get the X value of the Vector
double LMVector3::GetX() const {
	return _x;
}
// Get the Y value of the Vector
double LMVector3::GetY() const {
	return _y;
}
// Get the Z value of the Vector
double LMVector3::GetZ() const {
	return _z;
}

// Setter functions
// Set the X value of the Vector
void LMVector3::SetX(double x) {
	this->_x = x;
}
// Set the Y value of the Vector
void LMVector3::SetY(double y) {
	this->_y = y;
}
// Set the Z value of the Vector
void LMVector3::SetZ(double z) {
	this->_z = z;
}

// Equal

// Sum
LMVector3 LMVector3::operator+(const LMVector3& other) const {
	LMVector3 aux = LMVector3(
		this->_x + other._x,
		this->_y + other._y,
		this->_z + other._z);

	return aux;
}

LMVector3 LMVector3::operator+(const double& other) const {
	LMVector3 aux = LMVector3(
		this->_x + other,
		this->_y + other,
		this->_z + other);

	return aux;
}

// Sub
LMVector3 LMVector3::operator-(const LMVector3& other) const {
	LMVector3 aux = LMVector3(
		this->_x - other._x,
		this->_y - other._y,
		this->_z - other._z);

	return aux;
}
LMVector3 LMVector3::operator-(const double& other) const {
	LMVector3 aux = LMVector3(
		this->_x - other,
		this->_y - other,
		this->_z - other);

	return aux;
}

// Mul
LMVector3 LMVector3::operator*(const LMVector3& other) const {
	LMVector3 aux = LMVector3(
		this->_x * other._x,
		this->_y * other._y,
		this->_z * other._z);
	return aux;
}

LMVector3 LMVector3::operator*(const double& other) const {
	LMVector3 aux = LMVector3(
		this->_x * other,
		this->_y * other,
		this->_z * other);

	return aux;
}

// Div
LMVector3 LMVector3::operator/(const LMVector3& other) const {
	LMVector3 aux = LMVector3(
		this->_x / other._x,
		this->_y / other._y,
		this->_z / other._z);

	return aux;
}
LMVector3 LMVector3::operator/(const double& other) const {
	LMVector3 aux = LMVector3(
		this->_x / other,
		this->_y / other,
		this->_z / other);

	return aux;
}

// Dot product
double LMVector3::Dot(const LMVector3& other) const {
	return _x * other._x + _y * other._y + _z * other._z;
}

// Cross product
LMVector3 LMVector3::Cross(const LMVector3& other) const {
	return LMVector3(_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
}
// Cross product
LMVector3 LMVector3::Cross(const LMVector3& other, const LMVector3& axis) const {
	LMVector3 cross = Cross(other);
	if (cross.Dot(axis) < 0) {
		cross = cross * -1;
	}
	return cross;
}

// Magnitude
double LMVector3::Magnitude() const {
	return sqrt(_x * _x + _y * _y + _z * _z);
}

// Normalize
void LMVector3::Normalize() {
	double mag = Magnitude();
	if (mag > 0) {
		_x /= mag;
		_y /= mag;
		_z /= mag;
	}
}

// Angle between two vectors
double LMVector3::Angle(const LMVector3& other) const {
	double dot = Dot(other);
	double mag = Magnitude() * other.Magnitude();
	if (mag > 0) {
		return acos(dot / mag);
	}
	return 0;
}

//Angle between two vectors
double LMVector3::Angle(const LMVector3& other, const LMVector3& axis) const {
	double angle = Angle(other);
	LMVector3 cross = Cross(other);
	if (cross.Dot(axis) < 0) {
		angle = -angle;
	}

	angle = angle * 180 / M_PI;

	return angle;
}


//Angle between two vectors in degrees
double LMVector3::Angle(const LMVector3& other, const LMVector3& normal, const LMVector3& axis) const {
	double angle = Angle(other, normal);
	LMVector3 cross = Cross(other, normal);
	if (cross.Dot(axis) < 0) {
		angle = -angle;
	}

	angle = angle * 180 / M_PI;

	return angle;
}

// Rotate a vector around an axis in degrees
LMVector3 LMVector3::Rotate(const LMVector3& axis, double angle) {
	LMVector3 cross = axis.Cross(*this);
	LMVector3 dot = axis * axis.Dot(*this);
	LMVector3 cross2 = axis.Cross(cross);
	auto a = dot + cross * sin(angle * M_PI / 180. ) + cross2 * (1 - cos(angle * M_PI / 180.));

	this->_x = a.GetX();
	this->_y = a.GetY();
	this->_z = a.GetZ();

	return a;
}

//Get the perpendicular vector from two vectors
LMVector3 LMVector3::Perpendicular(const LMVector3& other) const {
	return Cross(other).Cross(*this);
}

LMQuaternion& LMVector3::AsRotToQuaternion() const {
	// Abbreviations for the various angular functions

	double cr = cos(this->_x * 0.5);
	double sr = sin(this->_x * 0.5);
	double cp = cos(this->_y * 0.5);
	double sp = sin(this->_y * 0.5);
	double cy = cos(this->_z * 0.5);
	double sy = sin(this->_z * 0.5);

	LMQuaternion q;
	q.SetW(cr * cp * cy + sr * sp * sy);
	q.SetX(sr * cp * cy - cr * sp * sy);
	q.SetY(cr * sp * cy + sr * cp * sy);
	q.SetZ(cr * cp * sy - sr * sp * cy);

	return q;
}





//Quaternion class to be used with LocoMotor

// Default constructor initializes quaternion to (1, 0, 0, 0)
LMQuaternion::LMQuaternion() : _w(1), _x(0), _y(0), _z(0) {
}

// Constructor initializes quaternion to specified values
LMQuaternion::LMQuaternion(double w, double x, double y, double z) : _w(w), _x(x), _y(y), _z(z) {
}

// Getter functions
double LMQuaternion::GetW() const {
	return _w;
}
double LMQuaternion::GetX() const {
	return _x;
}
double LMQuaternion::GetY() const {
	return _y;
}
double LMQuaternion::GetZ() const {
	return _z;
}

//Setter functions
void LMQuaternion::SetW(double w) {
	this->_w = w;
}
void LMQuaternion::SetX(double x) {
	this->_x = x;
}
void LMQuaternion::SetY(double y) {
	this->_y = y;
}
void LMQuaternion::SetZ(double z) {
	this->_z = z;
}

// Quaternion equal
LMQuaternion LMQuaternion::operator=(const LMQuaternion& other) {
	_w = other._w;
	_x = other._x;
	_y = other._y;
	_z = other._z;
	return *this;
}



// Quaternion addition
LMQuaternion LMQuaternion::operator+(const LMQuaternion& other) const {
	return LMQuaternion(_w + other._w, _x + other._x, _y + other._y, _z + other._z);
}


// Quaternion subtraction
LMQuaternion LMQuaternion::operator-(const LMQuaternion& other) const {
	return LMQuaternion(_w - other._w, _x - other._x, _y - other._y, _z - other._z);
}


// Quaternion multiplication
LMQuaternion LMQuaternion::operator*(const LMQuaternion& other) const {
	double newW = _w * other._w - _x * other._x - _y * other._y - _z * other._z;
	double newX = _w * other._x + _x * other._w + _y * other._z - _z * other._y;
	double newY = _w * other._y - _x * other._z + _y * other._w + _z * other._x;
	double newZ = _w * other._z + _x * other._y - _y * other._x + _z * other._w;
	return LMQuaternion(newW, newX, newY, newZ);
}
// Scalar multiplication
LMQuaternion LMQuaternion::operator*(double scalar) const {
	return LMQuaternion(_w * scalar, _x * scalar, _y * scalar, _z * scalar);
}

// Scalar division
LMQuaternion LMQuaternion::operator/(double scalar) const {
	return LMQuaternion(_w / scalar, _x / scalar, _y / scalar, _z / scalar);
}

// Conjugate
LMQuaternion LMQuaternion::Conjugate() const {
	return LMQuaternion(_w, -_x, -_y, -_z);
}

// Magnitude
double LMQuaternion::Magnitude() const {
	return sqrt(_w * _w + _x * _x + _y * _y + _z * _z);
}

// Normalize
void LMQuaternion::Normalize() {
	double mag = Magnitude();
	if (mag > 0) {
		_w /= mag;
		_x /= mag;
		_y /= mag;
		_z /= mag;
	}
}

//Rotate a quaternion
LMQuaternion LMQuaternion::Rotate(const LMVector3& axis, double angle) const 	{
	LMQuaternion q;
	double halfAngle = (angle * (M_PI / 180.0)) / 2.0;
	double sinHalfAngle = sin(halfAngle);
	q.SetW(cos(halfAngle));
	q.SetX(axis.GetX() * sinHalfAngle);
	q.SetY(axis.GetY() * sinHalfAngle);
	q.SetZ(axis.GetZ() * sinHalfAngle);
	return q * (*this);
}

// Rotate a vector by this quaternion
LMVector3 LMQuaternion::Rotate(const LMVector3& vector) const {
	LMQuaternion vectorQuat(0, vector.GetX(), vector.GetY(), vector.GetZ());
	LMQuaternion result = (*this) * vectorQuat * Conjugate();
	return LMVector3(result.GetX(), result.GetY(), result.GetZ());
}

// Up vector of this quaternion
LMVector3 LMQuaternion::Up() const {
	return Rotate(LMVector3(0, 1, 0));
}

// Right vector of this quaternion
LMVector3 LMQuaternion::Right() const {
	return Rotate(LMVector3(1, 0, 0));
}

// Forward vector of this quaternion
LMVector3 LMQuaternion::Forward() const {
	return Rotate(LMVector3(0, 0, -1));
}

LMVector3& LMQuaternion::ToEuler() const {
	LMVector3 angles;

// roll (x-axis rotation)
	double sinr_cosp = 2 * (this->_w * this->_x + this->_y * this->_z);
	double cosr_cosp = 1 - 2 * (this->_x * this->_x + this->_y * this->_y);
	angles.SetX(std::atan2(sinr_cosp, cosr_cosp));

	// pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (this->_w * this->_y - this->_x * this->_z));
	double cosp = std::sqrt(1 - 2 * (this->_w * this->_y - this->_x * this->_z));
	angles.SetY(2 * std::atan2(sinp, cosp) - M_PI / 2);

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (this->_w * this->_z + this->_x * this->_y);
	double cosy_cosp = 1 - 2 * (this->_y * this->_y + this->_z * this->_z);
	angles.SetZ(std::atan2(siny_cosp, cosy_cosp));

	return angles;
}


