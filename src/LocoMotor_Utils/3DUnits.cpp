#include "3DUnits.h"
#include "LMVector.h"


//VECTOR 3D
Vector3D::Vector3D() {
	_x = 0;
	_y = 0;
	_z = 0;
}

Vector3D::Vector3D(double x, double y, double z) {
	_x = x;
	_y = y;
	_z = z;
}

double Vector3D::GetX() const {
	return _x;
}

double Vector3D::GetY() const {
	return _y;
}

double Vector3D::GetZ() const {
	return _z;
}

void Vector3D::SetX(double x) {
	_x = x;
}

void Vector3D::SetY(double y) {
	_y = y;
}

void Vector3D::SetZ(double z) {
	_z = z;
}

Vector3D Vector3D::operator+(const Vector3D& other) {
	_x += other.GetX();
	_y += other.GetY();
	_z += other.GetZ();
	return *this;
}

Vector3D Vector3D::operator-(const Vector3D& other) {
	_x -= other.GetX();
	_y -= other.GetY();
	_z -= other.GetZ();
	return *this;
}

Vector3D Vector3D::operator*(const Vector3D& other) {
	_x *= other.GetX();
	_y *= other.GetY();
	_z *= other.GetZ();
	return *this;
}

Vector3D Vector3D::operator* (const double& other) {
	_x *= other;
	_y *= other;
	_z *= other;
	return *this;
}

Vector3D Vector3D::operator/(const Vector3D& other) {
	_x /= other.GetX();
	_y /= other.GetY();
	_z /= other.GetZ();
	return *this;
}

Vector3D Vector3D::operator/(const double& other) {
	_x /= other;
	_y /= other;
	_z /= other;
	return *this;
}

Vector3D::operator LMVector3() const {
	return LMVector3(_x, _y, _z);
}

Vector3D Vector3D::Normalize() {
	double magnitude = Magnitude();
	_x /= magnitude;
	_y /= magnitude;
	_z /= magnitude;
	return *this;
}

double Vector3D::Magnitude() {
	return sqrt(_x * _x + _y * _y + _z * _z);
}

Vector3D Vector3D::Lerp(Vector3D& other, double t) {
	return *this + (other - *this) * t;
}

double Vector3D::Distance(Vector3D& other) {
	return sqrt(pow(_x - other.GetX(), 2) + pow(_y - other.GetY(), 2) + pow(_z - other.GetZ(), 2));
}

Vector3D Vector3D::Rotate(Vector3D& axis, double& angle) {
	double sinHalfAngle = sin(angle / 2);
	double cosHalfAngle = cos(angle / 2);

	double rx = axis.GetX() * sinHalfAngle;
	double ry = axis.GetY() * sinHalfAngle;
	double rz = axis.GetZ() * sinHalfAngle;
	double rw = cosHalfAngle;

	Quaternion3D rotationQuaternion(rx, ry, rz, rw);
	Quaternion3D conjugateQuaternion = rotationQuaternion.Conjugate();
	Quaternion3D w = rotationQuaternion * *this * conjugateQuaternion;

	_x = w.GetX();
	_y = w.GetY();
	_z = w.GetZ();

	return *this;
}
}


//QUATERNION 3D

Quaternion3D::Quaternion3D() {
	_x = 0;
	_y = 0;
	_z = 0;
	_w = 0;
}

Quaternion3D::Quaternion3D(double x, double y, double z, double w) {
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

double Quaternion3D::GetX() const {
	return _x;
}

double Quaternion3D::GetY() const {
	return _y;
}

double Quaternion3D::GetZ() const {
	return _z;
}

double Quaternion3D::GetW() const {
	return _w;
}

void Quaternion3D::SetX(double x) {
	_x = x;
}

void Quaternion3D::SetY(double y) {
	_y = y;
}

void Quaternion3D::SetZ(double z) {
	_z = z;
}

void Quaternion3D::SetW(double w) {
	_w = w;
}

Quaternion3D Quaternion3D::operator+(const Quaternion3D& other){
	_x += other.GetX();
	_y += other.GetY();
	_z += other.GetZ();
	_w += other.GetW();
	return *this;
}

Quaternion3D Quaternion3D::operator-(const Quaternion3D& other) {
	_x -= other.GetX();
	_y -= other.GetY();
	_z -= other.GetZ();
	_w -= other.GetW();
	return *this;
}

Quaternion3D Quaternion3D::operator*(const Quaternion3D& other) {
	_x *= other.GetX();
	_y *= other.GetY();
	_z *= other.GetZ();
	_w *= other.GetW();
	return *this;
}

Quaternion3D Quaternion3D::operator* (const double& other) {
	_x *= other;
	_y *= other;
	_z *= other;
	_w *= other;
	return *this;
}

Quaternion3D Quaternion3D::operator/(const Quaternion3D& other) {
	_x /= other.GetX();
	_y /= other.GetY();
	_z /= other.GetZ();
	_w /= other.GetW();
	return *this;
}

Quaternion3D Quaternion3D::operator/(const double& other) {
	_x /= other;
	_y /= other;
	_z /= other;
	_w /= other;
	return *this;
}

Quaternion3D::operator LMQuaternion() const {
	return LMQuaternion(_x, _y, _z, _w);
}

