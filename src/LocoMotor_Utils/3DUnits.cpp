#include "3DUnits.h"
#include "LMVector.h"
#define _USE_MATH_DEFINES
#include <math.h>

//VECTOR 3D

//Default constructor initializes vector to (0, 0, 0)
Vector3D::Vector3D() {
	this->_x = 0;
	this->_y = 0;
	this->_z = 0;
}
//Constructor initializes vector to specified values
Vector3D::Vector3D(double x, double y, double z) {
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

//Getters
double Vector3D::GetX() const {
	return this->_x;
}
double Vector3D::GetY() const {
	return this->_y;
}
double Vector3D::GetZ() const {
	return this->_z;
}
//Setters
void Vector3D::SetX(double x) {
	this->_x = x;
}
void Vector3D::SetY(double y) {
	this->_y = y;
}
void Vector3D::SetZ(double z) {
	this->_z = z;
}

//Operators
Vector3D Vector3D::operator+(const Vector3D& other) {
	this->_x += other.GetX();
	this->_y += other.GetY();
	this->_z += other.GetZ();
	return *this;
}
Vector3D Vector3D::operator-(const Vector3D& other) {
	this->_x -= other.GetX();
	this->_y -= other.GetY();
	this->_z -= other.GetZ();
	return *this;
}
Vector3D Vector3D::operator*(const Vector3D& other) {
	this->_x *= other.GetX();
	this->_y *= other.GetY();
	this->_z *= other.GetZ();
	return *this;
}
Vector3D Vector3D::operator* (const double& other) {
	this->_x *= other;
	this->_y *= other;
	this->_z *= other;
	return *this;
}
Vector3D Vector3D::operator/(const Vector3D& other) {
	this->_x /= other.GetX();
	this->_y /= other.GetY();
	this->_z /= other.GetZ();
	return *this;
}
Vector3D Vector3D::operator/(const double& other) {
	this->_x /= other;
	this->_y /= other;
	this->_z /= other;
	return *this;
}

//LMVector3 translator for LocoMotor
Vector3D::operator LMVector3() const {
	return LMVector3(this->_x, this->_y, this->_z);
}

//Normalizes the vector
Vector3D Vector3D::Normalize() {
	double magnitude = Magnitude();
	this->_x /= magnitude;
	this->_y /= magnitude;
	this->_z /= magnitude;
	return *this;
}
//Magnitude of the vector
double Vector3D::Magnitude() {
	return sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
}
//Lerp between two vectors
Vector3D Vector3D::Lerp(Vector3D& other, double t) {
	return *this + (other - *this) * t;
}
//Distance between two vectors
double Vector3D::Distance(Vector3D& other) {
	return sqrt(pow(this->_x - other.GetX(), 2) + pow(this->_y - other.GetY(), 2) + pow(this->_z - other.GetZ(), 2));
}
//Rotate the vector around an axis
Vector3D Vector3D::Rotate(Vector3D& axis, double& angle) {
	Vector3D cross = axis.Cross(*this);
	Vector3D dot = axis * axis.Dot(*this);
	Vector3D cross2 = axis.Cross(cross);
	auto a = dot + cross * sin(angle * M_PI / 180.) + cross2 * (1 - cos(angle * M_PI / 180.));

	this->_x = a.GetX();
	this->_y = a.GetY();
	this->_z = a.GetZ();

	return a;
}
//Point the vector towards another vector
Vector3D Vector3D::PointTowards(Vector3D& other) {
	Vector3D dir = other - *this;
	dir.Normalize();
	return dir;
}
//Cross product of two vectors
Vector3D Vector3D::Cross(Vector3D& other) {
	return Vector3D(this->_y * other.GetZ() - this->_z * other.GetY(), this->_z * other.GetX() - this->_x * other.GetZ(), this->_x * other.GetY() - this->_y * other.GetX());
}
//dot product of two vectors
double Vector3D::Dot(Vector3D& other) {
	return this->_x * other.GetX() + this->_y * other.GetY() + this->_z * other.GetZ();
}



//QUATERNION 3D

//Default constructor initializes quaternion to (0, 0, 0, 0)
Quaternion3D::Quaternion3D() {
	this->_x = 0;
	this->_y = 0;
	this->_z = 0;
	this->_w = 0;
}
//Constructor initializes quaternion to specified values
Quaternion3D::Quaternion3D(double x, double y, double z, double w) {
	this->_x = x;
	this->_y = y;
	this->_z = z;
	this->_w = w;
}
//Getters
double Quaternion3D::GetX() const {
	return this->_x;
}
double Quaternion3D::GetY() const {
	return this->_y;
}
double Quaternion3D::GetZ() const {
	return this->_z;
}
double Quaternion3D::GetW() const {
	return this->_w;
}
//Setters
void Quaternion3D::SetX(double x) {
	this->_x = x;
}
void Quaternion3D::SetY(double y) {
	this->_y = y;
}
void Quaternion3D::SetZ(double z) {
	this->_z = z;
}
void Quaternion3D::SetW(double w) {
	this->_w = w;
}

//Operators
Quaternion3D Quaternion3D::operator+(const Quaternion3D& other){
	this->_x += other.GetX();
	this->_y += other.GetY();
	this->_z += other.GetZ();
	this->_w += other.GetW();
	return *this;
}
Quaternion3D Quaternion3D::operator-(const Quaternion3D& other) {
	this->_x -= other.GetX();
	this->_y -= other.GetY();
	this->_z -= other.GetZ();
	this->_w -= other.GetW();
	return *this;
}
Quaternion3D Quaternion3D::operator*(const Quaternion3D& other) {
	this->_x *= other.GetX();
	this->_y *= other.GetY();
	this->_z *= other.GetZ();
	this->_w *= other.GetW();
	return *this;
}
Quaternion3D Quaternion3D::operator* (const double& other) {
	this->_x *= other;
	this->_y *= other;
	this->_z *= other;
	this->_w *= other;
	return *this;
}
Quaternion3D Quaternion3D::operator/(const Quaternion3D& other) {
	this->_x /= other.GetX();
	this->_y /= other.GetY();
	this->_z /= other.GetZ();
	this->_w /= other.GetW();
	return *this;
}
Quaternion3D Quaternion3D::operator/(const double& other) {
	this->_x /= other;
	this->_y /= other;
	this->_z /= other;
	this->_w /= other;
	return *this;
}

//LMQuaternion conversion to use with LocoMotor
Quaternion3D::operator LMQuaternion() const {
	return LMQuaternion(this->_x, this->_y, this->_z, this->_w);
}

//Normalize the quaternion
Quaternion3D Quaternion3D::Normalize() {
	double magnitude = Magnitude();
	this->_x /= magnitude;
	this->_y /= magnitude;
	this->_z /= magnitude;
	this->_w /= magnitude;
	return *this;
}
//Magnitude of the quaternion
double Quaternion3D::Magnitude() {
	return sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z + this->_w * this->_w);
}
//Conjugate of the quaternion
Quaternion3D Quaternion3D::Conjugate() {
	return Quaternion3D(-this->_x, -this->_y, -this->_z, this->_w);
}
//Quaternion rotation along an axis
Quaternion3D Quaternion3D::Rotate(Vector3D& axis, double& degrees) {
	Quaternion3D q;
	double halfAngle = (degrees * (M_PI / 180.0)) / 2.0;
	double sinHalfAngle = sin(halfAngle);
	q.SetW(cos(halfAngle));
	q.SetX(axis.GetX() * sinHalfAngle);
	q.SetY(axis.GetY() * sinHalfAngle);
	q.SetZ(axis.GetZ() * sinHalfAngle);
	return q * (*this);
}
//Rotate a vector by a quaternion
Vector3D Quaternion3D::QuaternionRotate(Vector3D& other, Quaternion3D& quat) {
	Quaternion3D q = Quaternion3D(other.GetX(), other.GetY(), other.GetZ(), 0);
	Quaternion3D q2 = quat * q * quat.Conjugate();
	return Vector3D(q2.GetX(), q2.GetY(), q2.GetZ());
}


