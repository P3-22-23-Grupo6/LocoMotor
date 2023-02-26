#pragma once

#include "OgreVector3.h"
#include "OgreQuaternion.h"
#include "btBulletDynamicsCommon.h"
#include "fmod_common.h"

//Vector class to be used with LocoMotor
class lmVector3 {


public:
    // Default constructor initializes vector to (0, 0, 0)
    /// @brief Create a new Vector3 with everything set to 0
    lmVector3 () : _x (0), _y (0), _z (0) {
    }

    // Constructor initializes vector to specified values
    /// @brief Create a new Vector3
    lmVector3 (double x, double y, double z) : _x (x), _y (y), _z (z) {
    }

    // Getter functions
    double getX () const {
        return _x;
    }
    double getY () const {
        return _y;
    }
    double getZ () const {
        return _z;
    }

    // Setter functions
    void setX (double x) {
        this->_x = x;
    }
    void setY (double y) {
        this->_y = y;
    }
    void setZ (double z) {
        this->_z = z;
    }

    // Vector addition
    lmVector3 operator+(const lmVector3& other) const {
        return lmVector3 (_x + other._x, _y + other._y, _z + other._z);
    }

    // Vector subtraction
    lmVector3 operator-(const lmVector3& other) const {
        return lmVector3 (_x - other._x, _y - other._y, _z - other._z);
    }

    // Scalar multiplication
    lmVector3 operator*(double scalar) const {
        return lmVector3 (_x * scalar, _y * scalar, _z * scalar);
    }

    // Scalar division
    lmVector3 operator/(double scalar) const {
        return lmVector3 (_x / scalar, _y / scalar, _z / scalar);
    }

    lmVector3 operator= (btVector3 bulletVector) {
        return BulletToLm (bulletVector);
    }

    btVector3 operator= (lmVector3 lmVector) {
        return LmToBullet (lmVector);
    }

    lmVector3 operator= (Ogre::Vector3 ogreVector) {
        return OgreToLm (ogreVector);
    }

    // Dot product
    double dot (const lmVector3& other) const {
        return _x * other._x + _y * other._y + _z * other._z;
    }

    // Cross product
    lmVector3 cross (const lmVector3& other) const {
        return lmVector3 (_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
    }

    // Magnitude
    double magnitude () const {
        return sqrt (_x * _x + _y * _y + _z * _z);
    }

    // Normalize
    void normalize () {
        double mag = magnitude ();
        if (mag > 0) {
            _x /= mag;
            _y /= mag;
            _z /= mag;
        }
    }

// VECTOR TRANSFORMATIONS BETWEEN LANGUAGES
    /// @brief Converts a Bullet vector to lmVector
   static lmVector3 BulletToLm (const btVector3& bulletVector) {
        return lmVector3 (bulletVector.x (), bulletVector.y (), bulletVector.z ());
   }
   /// @brief Converts an lmVector to Bullet vector
   static btVector3 LmToBullet (const lmVector3& lmVector) {
       return btVector3 (lmVector.getX (), lmVector.getY (), lmVector.getZ ());
   }
   /// @brief Converts an Ogre vector to lmVector
   static lmVector3 OgreToLm (const Ogre::Vector3& ogreVector) {
       return lmVector3 (ogreVector.x, ogreVector.y, ogreVector.z);
   }
   /// @brief Converts an lmVector to an Ogre vector
   static Ogre::Vector3 LmToOgre (const lmVector3& lmVector) {
       return Ogre::Vector3 (lmVector.getX (), lmVector.getY (), lmVector.getZ ());
   }
   /// @brief Converts an FMod vector to an lmVector
   static lmVector3 FModToLm (const FMOD_VECTOR& fmVector) {
       return lmVector3 (fmVector.x, fmVector.y, fmVector.z);
   }
   /// @brief Converts an lmVector to an FMod vector
   static FMOD_VECTOR LmToFMod (const lmVector3& lmVector) {
       return FMOD_VECTOR{ (float) lmVector.getX (), (float) lmVector.getY (), (float) lmVector.getZ () };
   }
   /// @brief Converts a Bullet transform to lmVector
   static lmVector3 BullTransformToLm (const btTransform& bulletTransform) {
       return lmVector3 (bulletTransform.getOrigin ().x (), bulletTransform.getOrigin ().y (), bulletTransform.getOrigin ().z ());
   }
   /// @brief Converts an lmVector to a Bullet Transform
   static btTransform LmToBullTransform (const lmVector3& lmVector) {
       btTransform bulletTransform;
       bulletTransform.setIdentity ();
       bulletTransform.setOrigin (LmToBullet (lmVector));
       return bulletTransform;
   }

   
private:
    double _x = 0, _y = 0, _z = 0;


};

//Quaternion class to be used with LocoMotor
class lmQuaternion {

    
public:
    // Default constructor initializes quaternion to (0, 0, 0, 0)
    /// @brief Create a new Quaternion with everything set to 0
    lmQuaternion () : _w (0), _x (0), _y (0), _z (0) {
    }

    // Constructor initializes quaternion to specified values
    /// @brief Create a new Quaternion
    lmQuaternion (double w, double x, double y, double z) : _w (w), _x (x), _y (y), _z (z) {
    }

    // Getter functions
    double getW () const {
        return _w;
    }
    double getX () const {
        return _x;
    }
    double getY () const {
        return _y;
    }
    double getZ () const {
        return _z;
    }

//Setter functions
    void setW (double w) {
        this->_w = w;
    }
    void setX (double x) {
        this->_x = x;
    }
    void setY (double y) {
        this->_y = y;
    }
    void setZ (double z) {
        this->_z = z;
    }

    // Quaternion addition
    lmQuaternion operator+(const lmQuaternion& other) const {
        return lmQuaternion (_w + other._w, _x + other._x, _y + other._y, _z + other._z);
    }

    // Quaternion subtraction
    lmQuaternion operator-(const lmQuaternion& other) const {
        return lmQuaternion (_w - other._w, _x - other._x, _y - other._y, _z - other._z);
    }

    // Quaternion multiplication
    lmQuaternion operator*(const lmQuaternion& other) const {
        double newW = _w * other._w - _x * other._x - _y * other._y - _z * other._z;
        double newX = _w * other._x + _x * other._w + _y * other._z - _z * other._y;
        double newY = _w * other._y - _x * other._z + _y * other._w + _z * other._x;
        double newZ = _w * other._z + _x * other._y - _y * other._x + _z * other._w;
        return lmQuaternion (newW, newX, newY, newZ);
    }

    // Scalar multiplication
    lmQuaternion operator*(double scalar) const {
        return lmQuaternion (_w * scalar, _x * scalar, _y * scalar, _z * scalar);
    }

    // Scalar division
    lmQuaternion operator/(double scalar) const {
        return lmQuaternion (_w / scalar, _x / scalar, _y / scalar, _z / scalar);
    }

    // Conjugate
    lmQuaternion conjugate () const {
        return lmQuaternion (_w, -_x, -_y, -_z);
    }

    // Magnitude
    double magnitude () const {
        return sqrt (_w * _w + _x * _x + _y * _y + _z * _z);
    }

    // Normalize
    void normalize () {
        double mag = magnitude ();
        if (mag > 0) {
            _w /= mag;
            _x /= mag;
            _y /= mag;
            _z /= mag;
        }
    }


// QUATERNION TRANSFORMATIONS BETWEEN LANGUAGES
    /// @brief Converts a Bullet quaternion to lmQuaternion
    static lmQuaternion BulletToLm (const btQuaternion& bulletQuaternion) {
        return lmQuaternion (bulletQuaternion.w(), bulletQuaternion.x (), bulletQuaternion.y (), bulletQuaternion.z ());
    }
    /// @brief Converts an lmQuaternion to Bullet vector
    static btQuaternion LmToBullet (const lmQuaternion& lmQuaternion) {
        return btQuaternion (lmQuaternion.getX (), lmQuaternion.getY (), lmQuaternion.getZ (), lmQuaternion.getW ());
    }
    /// @brief Converts an Ogre quaternion to lmQuaternion
    static lmQuaternion OgreToLm (const Ogre::Quaternion& ogreQuaternion) {
        return lmQuaternion (ogreQuaternion.w, ogreQuaternion.x, ogreQuaternion.y, ogreQuaternion.z);
    }
    /// @brief Converts an lmQuaternion to an Ogre quaternion
    static Ogre::Quaternion LmToOgre (const lmQuaternion& lmQuaternion) {
        return Ogre::Quaternion (lmQuaternion.getW(), lmQuaternion.getX (), lmQuaternion.getY (), lmQuaternion.getZ ());
    }
    /// @brief Converts a Bullet transform to lmQuaternion
    lmQuaternion BullTransformToLm (btTransform bulletTransform) {
        return lmQuaternion (bulletTransform.getRotation ().w (), bulletTransform.getRotation ().x (), bulletTransform.getRotation ().y (), bulletTransform.getRotation ().z ());
    }
    /// @brief Converts an lmQuaternion to a Bullet Transform
    btTransform LmToBullTransform (lmQuaternion lmQuaternion) {
        btTransform bulletTransform;
        bulletTransform.setIdentity ();
        bulletTransform.setRotation (LmToBullet (lmQuaternion));
        return bulletTransform;
    }
    /// @brief Converts an lmVector and lmQuaternion to a Bullet Transform
    btTransform LmToBullTransform (lmVector3 lmVector, lmQuaternion lmQuaternion) {
        btTransform bulletTransform;
        bulletTransform.setIdentity ();
        bulletTransform.setOrigin (lmVector3::LmToBullet (lmVector));
        bulletTransform.setRotation (LmToBullet (lmQuaternion));
        return bulletTransform;
    }

    

private:
     double _w = 0, _x = 0, _y = 0 , _z = 0;

     
};