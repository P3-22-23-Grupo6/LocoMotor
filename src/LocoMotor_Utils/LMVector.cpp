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
LMVector3 LMVector3::operator=(const Ogre::Vector3& v) {
	*this = OgreToLm(v);

	return *this;
}
LMVector3 LMVector3::operator=(const FMOD_VECTOR& v) {
	*this = FModToLm(v);

	return *this;
}
LMVector3 LMVector3::operator=(const btVector3& v) {
	*this = BulletToLm(v);
	return *this;
}
LMVector3 LMVector3::operator=(const btTransform& v) {
	*this = BullTransformToLm(v);
	return *this;
}

// Sum
LMVector3 LMVector3::operator+(const LMVector3& other) const {
	LMVector3 aux = LMVector3(
		this->_x + other._x,
		this->_y + other._y,
		this->_z + other._z);

	return aux;
}
LMVector3 LMVector3::operator+(const btVector3& other) const {
	return *this + BulletToLm(other);
}
LMVector3 LMVector3::operator+(const btTransform& other) const {
	return *this + BullTransformToLm(other);
}
LMVector3 LMVector3::operator+(const Ogre::Vector3& other) const {
	return *this + OgreToLm(other);
}
LMVector3 LMVector3::operator+(const FMOD_VECTOR& other) const {
	return *this + FModToLm(other);
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
LMVector3 LMVector3::operator-(const btVector3& other) const {
	return *this - BulletToLm(other);
}
LMVector3 LMVector3::operator-(const btTransform& other) const {
	return *this - BullTransformToLm(other);
}
LMVector3 LMVector3::operator-(const Ogre::Vector3& other) const {
	return *this - OgreToLm(other);
}
LMVector3 LMVector3::operator-(const FMOD_VECTOR& other) const {
	return *this - FModToLm(other);
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
LMVector3 LMVector3::operator*(const btVector3& other) const {
	return *this * BulletToLm(other);
}
LMVector3 LMVector3::operator*(const btTransform& other) const {
	return *this * BullTransformToLm(other);
}
LMVector3 LMVector3::operator*(const Ogre::Vector3& other) const {
	return *this * OgreToLm(other);
}
LMVector3 LMVector3::operator*(const FMOD_VECTOR& other) const {
	return *this * FModToLm(other);
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
LMVector3 LMVector3::operator/(const btVector3& other) const {
	return *this / BulletToLm(other);
}
LMVector3 LMVector3::operator/(const btTransform& other) const {
	return *this / BullTransformToLm(other);
}
LMVector3 LMVector3::operator/(const Ogre::Vector3& other) const {
	return *this / OgreToLm(other);
}
LMVector3 LMVector3::operator/(const FMOD_VECTOR& other) const {
	return *this / FModToLm(other);
}
LMVector3 LMVector3::operator/(const double& other) const {
	LMVector3 aux = LMVector3(
		this->_x / other,
		this->_y / other,
		this->_z / other);

	return aux;
}

// Type operators
LMVector3::operator Ogre::Vector3() const {
	return LmToOgre(*this);
}

/*LMVector3::operator btVector3() const {
	return LmToBullet(*this);
}*/ //Refer to lmVector.h for explanations on why this doesn't work

LMVector3::operator btTransform() const {
	return LmToBullTransform(*this);
}

LMVector3::operator FMOD_VECTOR() const {
	return LmToFMod(*this);
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
}






// VECTOR TRANSFORMATIONS BETWEEN LANGUAGES
// Converts a Bullet vector to lmVector
LMVector3 LMVector3::BulletToLm(const btVector3& bulletVector) {
	return LMVector3(bulletVector.x(), bulletVector.y(), bulletVector.z());
}
// Converts an lmVector to Bullet vector
btVector3 LMVector3::LmToBullet(const LMVector3& lmVector) {
	return btVector3(lmVector.GetX(), lmVector.GetY(), lmVector.GetZ());
}
// Converts an Ogre vector to lmVector
LMVector3 LMVector3::OgreToLm(const Ogre::Vector3& ogreVector) {
	return LMVector3(ogreVector.x, ogreVector.y, ogreVector.z);
}
// Converts an lmVector to an Ogre vector
Ogre::Vector3 LMVector3::LmToOgre(const LMVector3& lmVector) {
	return Ogre::Vector3((double) lmVector.GetX(), (double) lmVector.GetY(), (double) lmVector.GetZ());
}
// Converts an FMod vector to an lmVector
LMVector3 LMVector3::FModToLm(const FMOD_VECTOR& fmVector) {
	return LMVector3(fmVector.x, fmVector.y, fmVector.z);
}
// Converts an lmVector to an FMod vector
FMOD_VECTOR LMVector3::LmToFMod(const LMVector3& lmVector) {
	return FMOD_VECTOR{ (float) lmVector.GetX(), (float) lmVector.GetY(), (float) lmVector.GetZ() };
}
// Converts a Bullet transform to lmVector
LMVector3 LMVector3::BullTransformToLm(const btTransform& bulletTransform) {
	return LMVector3(bulletTransform.getOrigin().x(), bulletTransform.getOrigin().y(), bulletTransform.getOrigin().z());
}
// Converts an lmVector to a Bullet Transform
btTransform LMVector3::LmToBullTransform(const LMVector3& lmVector) {
	btTransform bulletTransform;
	bulletTransform.setIdentity();
	bulletTransform.setOrigin(LmToBullet(lmVector));
	return bulletTransform;
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
LMQuaternion LMQuaternion::operator=(const btQuaternion& other) {
	_w = other.getW();
	_x = other.getX();
	_y = other.getY();
	_z = other.getZ();
	return *this;
}
LMQuaternion LMQuaternion::operator=(const btTransform& other) {
	_w = other.getRotation().getW();
	_x = other.getRotation().getX();
	_y = other.getRotation().getY();
	_z = other.getRotation().getZ();
	return *this;
}
LMQuaternion LMQuaternion::operator=(const Ogre::Quaternion& other) {
	_w = other.w;
	_x = other.x;
	_y = other.y;
	_z = other.z;
	return *this;
}


// Quaternion addition
LMQuaternion LMQuaternion::operator+(const LMQuaternion& other) const {
	return LMQuaternion(_w + other._w, _x + other._x, _y + other._y, _z + other._z);
}
LMQuaternion LMQuaternion::operator+(const btQuaternion& other) const {
	return LMQuaternion(_w + other.getW(), _x + other.getX(), _y + other.getY(), _z + other.getZ());
}
LMQuaternion LMQuaternion::operator+(const btTransform& other) const {
	return LMQuaternion(_w + other.getRotation().getW(), _x + other.getRotation().getX(), _y + other.getRotation().getY(), _z + other.getRotation().getZ());
}
LMQuaternion LMQuaternion::operator+(const Ogre::Quaternion& other) const {
	return LMQuaternion(_w + other.w, _x + other.x, _y + other.y, _z + other.z);
}

// Quaternion subtraction
LMQuaternion LMQuaternion::operator-(const LMQuaternion& other) const {
	return LMQuaternion(_w - other._w, _x - other._x, _y - other._y, _z - other._z);
}
LMQuaternion LMQuaternion::operator-(const btQuaternion& other) const {
	return LMQuaternion(_w - other.getW(), _x - other.getX(), _y - other.getY(), _z - other.getZ());
}
LMQuaternion LMQuaternion::operator-(const btTransform& other) const {
	return LMQuaternion(_w - other.getRotation().getW(), _x - other.getRotation().getX(), _y - other.getRotation().getY(), _z - other.getRotation().getZ());
}
LMQuaternion LMQuaternion::operator-(const Ogre::Quaternion& other) const {
	return LMQuaternion(_w - other.w, _x - other.x, _y - other.y, _z - other.z);
}

// Quaternion multiplication
LMQuaternion LMQuaternion::operator*(const LMQuaternion& other) const {
	double newW = _w * other._w - _x * other._x - _y * other._y - _z * other._z;
	double newX = _w * other._x + _x * other._w + _y * other._z - _z * other._y;
	double newY = _w * other._y - _x * other._z + _y * other._w + _z * other._x;
	double newZ = _w * other._z + _x * other._y - _y * other._x + _z * other._w;
	return LMQuaternion(newW, newX, newY, newZ);
}
LMQuaternion LMQuaternion::operator*(const btQuaternion& other) const {
	double newW = _w * other.getW() - _x * other.getX() - _y * other.getY() - _z * other.getZ();
	double newX = _w * other.getX() + _x * other.getW() + _y * other.getZ() - _z * other.getY();
	double newY = _w * other.getY() - _x * other.getZ() + _y * other.getW() + _z * other.getX();
	double newZ = _w * other.getZ() + _x * other.getY() - _y * other.getX() + _z * other.getW();
	return LMQuaternion(newW, newX, newY, newZ);
}
LMQuaternion LMQuaternion::operator*(const btTransform& other) const {
	double newW = _w * other.getRotation().getW() - _x * other.getRotation().getX() - _y * other.getRotation().getY() - _z * other.getRotation().getZ();
	double newX = _w * other.getRotation().getX() + _x * other.getRotation().getW() + _y * other.getRotation().getZ() - _z * other.getRotation().getY();
	double newY = _w * other.getRotation().getY() - _x * other.getRotation().getZ() + _y * other.getRotation().getW() + _z * other.getRotation().getX();
	double newZ = _w * other.getRotation().getZ() + _x * other.getRotation().getY() - _y * other.getRotation().getX() + _z * other.getRotation().getW();
	return LMQuaternion(newW, newX, newY, newZ);
}
LMQuaternion LMQuaternion::operator*(const Ogre::Quaternion& other) const {
	double newW = _w * other.w - _x * other.x - _y * other.y - _z * other.z;
	double newX = _w * other.x + _x * other.w + _y * other.z - _z * other.y;
	double newY = _w * other.y - _x * other.z + _y * other.w + _z * other.x;
	double newZ = _w * other.z + _x * other.y - _y * other.x + _z * other.w;
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
	return q;
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


// QUATERNION TRANSFORMATIONS BETWEEN LANGUAGES
// Converts a Bullet quaternion to LMQuaternion
LMQuaternion LMQuaternion::BulletToLm(const btQuaternion& bulletQuaternion) {
	return LMQuaternion(bulletQuaternion.w(), bulletQuaternion.x(), bulletQuaternion.y(), bulletQuaternion.z());
}
// Converts an LMQuaternion to Bullet vector
btQuaternion LMQuaternion::LmToBullet(const LMQuaternion& LMQuaternion) {
	return btQuaternion(LMQuaternion.GetX(), LMQuaternion.GetY(), LMQuaternion.GetZ(), LMQuaternion.GetW());
}
// Converts an Ogre quaternion to LMQuaternion
LMQuaternion LMQuaternion::OgreToLm(const Ogre::Quaternion& ogreQuaternion) {
	return LMQuaternion(ogreQuaternion.w, ogreQuaternion.x, ogreQuaternion.y, ogreQuaternion.z);
}
// Converts an LMQuaternion to an Ogre quaternion
Ogre::Quaternion LMQuaternion::LmToOgre(const LMQuaternion& LMQuaternion) {
	return Ogre::Quaternion(LMQuaternion.GetW(), LMQuaternion.GetX(), LMQuaternion.GetY(), LMQuaternion.GetZ());
}
// Converts a Bullet transform to LMQuaternion
LMQuaternion LMQuaternion::BullTransformToLm(btTransform bulletTransform) {
	return LMQuaternion(bulletTransform.getRotation().w(), bulletTransform.getRotation().x(), bulletTransform.getRotation().y(), bulletTransform.getRotation().z());
}
// Converts an LMQuaternion to a Bullet Transform
btTransform LMQuaternion::LmToBullTransform(LMQuaternion LMQuaternion) {
	btTransform bulletTransform;
	bulletTransform.setIdentity();
	bulletTransform.setRotation(LmToBullet(LMQuaternion));
	return bulletTransform;
}
// Converts an lmVector and LMQuaternion to a Bullet Transform
btTransform LMQuaternion::LmToBullTransform(LMVector3 lmVector, LMQuaternion LMQuaternion) {
	btTransform bulletTransform;
	bulletTransform.setIdentity();
	bulletTransform.setOrigin(LMVector3::LmToBullet(lmVector));
	bulletTransform.setRotation(LmToBullet(LMQuaternion));
	return bulletTransform;
}
