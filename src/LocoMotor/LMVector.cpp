#include "LMVector.h"

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
    LMVector3 () : _x (0), _y (0), _z (0) {
    }

    // Constructor initializes vector to specified values
    /// @brief Create a new Vector3
    LMVector3 (double x, double y, double z) : _x (x), _y (y), _z (z) {
    }

    // Getter functions
    double GetX () const {
        return _x;
    }
    double GetY () const {
        return _y;
    }
    double GetZ () const {
        return _z;
    }

    // Setter functions
    void SetX (double x) {
        this->_x = x;
    }
    void SetY (double y) {
        this->_y = y;
    }
    void SetZ (double z) {
        this->_z = z;
    }

    // Vector addition
    LMVector3 operator+(const LMVector3& other) const {
        return LMVector3 (_x + other._x, _y + other._y, _z + other._z);
    }

    // Vector subtraction
    LMVector3 operator-(const LMVector3& other) const {
        return LMVector3 (_x - other._x, _y - other._y, _z - other._z);
    }

    // Scalar multiplication
    LMVector3 operator*(double scalar) const {
        return LMVector3 (_x * scalar, _y * scalar, _z * scalar);
    }

    // Scalar division
    LMVector3 operator/(double scalar) const {
        return LMVector3 (_x / scalar, _y / scalar, _z / scalar);
    }

    LMVector3 operator= (btVector3 bulletVector) {
        return BulletToLm (bulletVector);
    }

    btVector3 operator= (LMVector3 lmVector) {
        return LmToBullet (lmVector);
    }

    LMVector3 operator= (Ogre::Vector3 ogreVector) {
        return OgreToLm (ogreVector);
    }

    // Dot product
    double Dot (const LMVector3& other) const {
        return _x * other._x + _y * other._y + _z * other._z;
    }

    // Cross product
    LMVector3 Cross (const LMVector3& other) const {
        return LMVector3 (_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
    }

    // Magnitude
    double Magnitude () const {
        return sqrt (_x * _x + _y * _y + _z * _z);
    }

    // Normalize
    void Normalize () {
        double mag = Magnitude ();
        if (mag > 0) {
            _x /= mag;
            _y /= mag;
            _z /= mag;
        }
    }

// VECTOR TRANSFORMATIONS BETWEEN LANGUAGES
    /// @brief Converts a Bullet vector to lmVector
    static LMVector3 BulletToLm (const btVector3& bulletVector) {
        return LMVector3 (bulletVector.x (), bulletVector.y (), bulletVector.z ());
    }
    /// @brief Converts an lmVector to Bullet vector
    static btVector3 LmToBullet (const LMVector3& lmVector) {
        return btVector3 (lmVector.GetX (), lmVector.GetY (), lmVector.GetZ ());
    }
    /// @brief Converts an Ogre vector to lmVector
    static LMVector3 OgreToLm (const Ogre::Vector3& ogreVector) {
        return LMVector3 (ogreVector.x, ogreVector.y, ogreVector.z);
    }
    /// @brief Converts an lmVector to an Ogre vector
    static Ogre::Vector3 LmToOgre (const LMVector3& lmVector) {
        return Ogre::Vector3 (lmVector.GetX (), lmVector.GetY (), lmVector.GetZ ());
    }
    /// @brief Converts an FMod vector to an lmVector
    static LMVector3 FModToLm (const FMOD_VECTOR& fmVector) {
        return LMVector3 (fmVector.x, fmVector.y, fmVector.z);
    }
    /// @brief Converts an lmVector to an FMod vector
    static FMOD_VECTOR LmToFMod (const LMVector3& lmVector) {
        return FMOD_VECTOR{ (float) lmVector.GetX (), (float) lmVector.GetY (), (float) lmVector.GetZ () };
    }
    /// @brief Converts a Bullet transform to lmVector
    static LMVector3 BullTransformToLm (const btTransform& bulletTransform) {
        return LMVector3 (bulletTransform.getOrigin ().x (), bulletTransform.getOrigin ().y (), bulletTransform.getOrigin ().z ());
    }
    /// @brief Converts an lmVector to a Bullet Transform
    static btTransform LmToBullTransform (const LMVector3& lmVector) {
        btTransform bulletTransform;
        bulletTransform.setIdentity ();
        bulletTransform.setOrigin (LmToBullet (lmVector));
        return bulletTransform;
    }


private:
    double _x = 0, _y = 0, _z = 0;


};

//Quaternion class to be used with LocoMotor
class LMQuaternion {


public:
    // Default constructor initializes quaternion to (0, 0, 0, 0)
    /// @brief Create a new Quaternion with everything Set to 0
    LMQuaternion () : _w (0), _x (0), _y (0), _z (0) {
    }

    // Constructor initializes quaternion to specified values
    /// @brief Create a new Quaternion
    LMQuaternion (double w, double x, double y, double z) : _w (w), _x (x), _y (y), _z (z) {
    }

    // Getter functions
    double GetW () const {
        return _w;
    }
    double GetX () const {
        return _x;
    }
    double GetY () const {
        return _y;
    }
    double GetZ () const {
        return _z;
    }

//Setter functions
    void SetW (double w) {
        this->_w = w;
    }
    void SetX (double x) {
        this->_x = x;
    }
    void SetY (double y) {
        this->_y = y;
    }
    void SetZ (double z) {
        this->_z = z;
    }

    // Quaternion addition
    LMQuaternion operator+(const LMQuaternion& other) const {
        return LMQuaternion (_w + other._w, _x + other._x, _y + other._y, _z + other._z);
    }

    // Quaternion subtraction
    LMQuaternion operator-(const LMQuaternion& other) const {
        return LMQuaternion (_w - other._w, _x - other._x, _y - other._y, _z - other._z);
    }

    // Quaternion multiplication
    LMQuaternion operator*(const LMQuaternion& other) const {
        double newW = _w * other._w - _x * other._x - _y * other._y - _z * other._z;
        double newX = _w * other._x + _x * other._w + _y * other._z - _z * other._y;
        double newY = _w * other._y - _x * other._z + _y * other._w + _z * other._x;
        double newZ = _w * other._z + _x * other._y - _y * other._x + _z * other._w;
        return LMQuaternion (newW, newX, newY, newZ);
    }

    // Scalar multiplication
    LMQuaternion operator*(double scalar) const {
        return LMQuaternion (_w * scalar, _x * scalar, _y * scalar, _z * scalar);
    }

    // Scalar division
    LMQuaternion operator/(double scalar) const {
        return LMQuaternion (_w / scalar, _x / scalar, _y / scalar, _z / scalar);
    }

    // Conjugate
    LMQuaternion Conjugate () const {
        return LMQuaternion (_w, -_x, -_y, -_z);
    }

    // Magnitude
    double Magnitude () const {
        return sqrt (_w * _w + _x * _x + _y * _y + _z * _z);
    }

    // Normalize
    void Normalize () {
        double mag = Magnitude ();
        if (mag > 0) {
            _w /= mag;
            _x /= mag;
            _y /= mag;
            _z /= mag;
        }
    }


// QUATERNION TRANSFORMATIONS BETWEEN LANGUAGES
    /// @brief Converts a Bullet quaternion to LMQuaternion
    static LMQuaternion BulletToLm (const btQuaternion& bulletQuaternion) {
        return LMQuaternion (bulletQuaternion.w (), bulletQuaternion.x (), bulletQuaternion.y (), bulletQuaternion.z ());
    }
    /// @brief Converts an LMQuaternion to Bullet vector
    static btQuaternion LmToBullet (const LMQuaternion& LMQuaternion) {
        return btQuaternion (LMQuaternion.GetX (), LMQuaternion.GetY (), LMQuaternion.GetZ (), LMQuaternion.GetW ());
    }
    /// @brief Converts an Ogre quaternion to LMQuaternion
    static LMQuaternion OgreToLm (const Ogre::Quaternion& ogreQuaternion) {
        return LMQuaternion (ogreQuaternion.w, ogreQuaternion.x, ogreQuaternion.y, ogreQuaternion.z);
    }
    /// @brief Converts an LMQuaternion to an Ogre quaternion
    static Ogre::Quaternion LmToOgre (const LMQuaternion& LMQuaternion) {
        return Ogre::Quaternion (LMQuaternion.GetW (), LMQuaternion.GetX (), LMQuaternion.GetY (), LMQuaternion.GetZ ());
    }
    /// @brief Converts a Bullet transform to LMQuaternion
    LMQuaternion BullTransformToLm (btTransform bulletTransform) {
        return LMQuaternion (bulletTransform.getRotation ().w (), bulletTransform.getRotation ().x (), bulletTransform.getRotation ().y (), bulletTransform.getRotation ().z ());
    }
    /// @brief Converts an LMQuaternion to a Bullet Transform
    btTransform LmToBullTransform (LMQuaternion LMQuaternion) {
        btTransform bulletTransform;
        bulletTransform.setIdentity ();
        bulletTransform.setRotation (LmToBullet (LMQuaternion));
        return bulletTransform;
    }
    /// @brief Converts an lmVector and LMQuaternion to a Bullet Transform
    btTransform LmToBullTransform (LMVector3 lmVector, LMQuaternion LMQuaternion) {
        btTransform bulletTransform;
        bulletTransform.setIdentity ();
        bulletTransform.setOrigin (LMVector3::LmToBullet (lmVector));
        bulletTransform.setRotation (LmToBullet (LMQuaternion));
        return bulletTransform;
    }



private:
    double _w = 0, _x = 0, _y = 0, _z = 0;


};