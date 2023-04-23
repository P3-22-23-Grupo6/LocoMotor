#pragma once
#ifndef _LMVECTOR_CONVERTER_
#define _LMVECTOR_CONVERTER_
#include "OgreVector.h"
#include "btBulletDynamicsCommon.h"
#include "fmod_common.h"
class LMVector3;
class LMQuaternion;

// VECTOR TRANSFORMATIONS BETWEEN LANGUAGES
	/// @brief Converts a Bullet vector to lmVector
LMVector3 BulletToLm(const btVector3& bulletVector);
/// @brief Converts an lmVector to Bullet vector
btVector3 LmToBullet(const LMVector3& lmVector);
/// @brief Converts an Ogre vector to lmVector
LMVector3 OgreToLm(const Ogre::Vector3& ogreVector);
/// @brief Converts an lmVector to an Ogre vector
Ogre::Vector3 LmToOgre(const LMVector3& lmVector);
/// @brief Converts an FMod vector to an lmVector
LMVector3 FModToLm(const FMOD_VECTOR& fmVector);
/// @brief Converts an lmVector to an FMod vector
FMOD_VECTOR LmToFMod(const LMVector3& lmVector);
/// @brief Converts a Bullet transform to lmVector
LMVector3 BullTransformToLm(const btTransform& bulletTransform);
/// @brief Converts an lmVector to a Bullet Transform
btTransform LmToBullTransform(const LMVector3& lmVector);

LMQuaternion BulletToLm(const btQuaternion& bulletQuaternion);
/// @brief Converts an LMQuaternion to Bullet vector
btQuaternion LmToBullet(const LMQuaternion& LMQuaternion);
/// @brief Converts an Ogre quaternion to LMQuaternion
LMQuaternion OgreToLm(const Ogre::Quaternion& ogreQuaternion);
/// @brief Converts an LMQuaternion to an Ogre quaternion
Ogre::Quaternion LmToOgre(const LMQuaternion& LMQuaternion);
/// @brief Converts a Bullet transform to LMQuaternion
LMQuaternion BullTransformToLm(btTransform bulletTransform);
/// @brief Converts an LMQuaternion to a Bullet Transform
btTransform LmToBullTransform(LMQuaternion LMQuaternion);
/// @brief Converts an lmVector and LMQuaternion to a Bullet Transform
btTransform LmToBullTransform(LMVector3 lmVector, LMQuaternion LMQuaternion);

#endif // !_LMVECTOR_COMVERTER_
