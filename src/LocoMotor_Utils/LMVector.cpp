#include "LMVector.h"
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

// Vector addition
LMVector3 LMVector3::operator+(const LMVector3& other) const {
	return LMVector3(_x + other._x, _y + other._y, _z + other._z);
}

// Vector subtraction
LMVector3 LMVector3::operator-(const LMVector3& other) const {
	return LMVector3(_x - other._x, _y - other._y, _z - other._z);
}

// Scalar multiplication
LMVector3 LMVector3::operator*(double scalar) const {
	return LMVector3(_x * scalar, _y * scalar, _z * scalar);
}

// Scalar division
LMVector3 LMVector3::operator/(double scalar) const {
	return LMVector3(_x / scalar, _y / scalar, _z / scalar);
}

LMVector3 LMVector3::operator= (const LMVector3& lmVector) {
	this->_x = lmVector._x;
	this->_y = lmVector._y;
	this->_z = lmVector._z;
	return lmVector;
}

LMVector3 LMVector3::operator= (btVector3& bulletVector) {
	this->_x = bulletVector.x();
	this->_y = bulletVector.y();
	this->_z = bulletVector.z();
	return BulletToLm(bulletVector);
}

LMVector3 LMVector3::operator= (Ogre::Vector3& ogreVector) {
	this->_x = ogreVector.x;
	this->_y = ogreVector.y;
	this->_z = ogreVector.z;
	return OgreToLm(ogreVector);
}

// Dot product
double LMVector3::Dot(const LMVector3& other) const {
	return _x * other._x + _y * other._y + _z * other._z;
}

// Cross product
LMVector3 LMVector3::Cross(const LMVector3& other) const {
	return LMVector3(_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
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
	return Ogre::Vector3(lmVector.GetX(), lmVector.GetY(), lmVector.GetZ());
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
