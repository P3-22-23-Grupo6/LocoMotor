#include "LmVectorConverter.h"
#include "LMVector.h"

// VECTOR TRANSFORMATIONS BETWEEN LANGUAGES
// Converts a Bullet vector to lmVector
LMVector3 BulletToLm(const btVector3& bulletVector) {
	return LMVector3(bulletVector.x(), bulletVector.y(), bulletVector.z());
}
// Converts an lmVector to Bullet vector
btVector3 LmToBullet(const LMVector3& lmVector) {
	return btVector3((float) lmVector.GetX(), (float) lmVector.GetY(), (float) lmVector.GetZ());
}
// Converts an Ogre vector to lmVector
LMVector3 OgreToLm(const Ogre::Vector3& ogreVector) {
	return LMVector3(ogreVector.x, ogreVector.y, ogreVector.z);
}
// Converts an lmVector to an Ogre vector
Ogre::Vector3 LmToOgre(const LMVector3& lmVector) {
	return Ogre::Vector3((float) lmVector.GetX(), (float) lmVector.GetY(), (float) lmVector.GetZ());
}
// Converts an FMod vector to an lmVector
LMVector3 FModToLm(const FMOD_VECTOR& fmVector) {
	return LMVector3(fmVector.x, fmVector.y, fmVector.z);
}
// Converts an lmVector to an FMod vector
FMOD_VECTOR LmToFMod(const LMVector3& lmVector) {
	return FMOD_VECTOR{ (float) lmVector.GetX(), (float) lmVector.GetY(), (float) lmVector.GetZ() };
}
// Converts a Bullet transform to lmVector
LMVector3 BullTransformToLm(const btTransform& bulletTransform) {
	return LMVector3(bulletTransform.getOrigin().x(), bulletTransform.getOrigin().y(), bulletTransform.getOrigin().z());
}
// Converts an lmVector to a Bullet Transform
btTransform LmToBullTransform(const LMVector3& lmVector) {
	btTransform bulletTransform;
	bulletTransform.setIdentity();
	bulletTransform.setOrigin(LmToBullet(lmVector));
	return bulletTransform;
}

// QUATERNION TRANSFORMATIONS BETWEEN LANGUAGES
// Converts a Bullet quaternion to LMQuaternion
LMQuaternion BulletToLm(const btQuaternion& bulletQuaternion) {
	return LMQuaternion(bulletQuaternion.w(), bulletQuaternion.x(), bulletQuaternion.y(), bulletQuaternion.z());
}
// Converts an LMQuaternion to Bullet vector
btQuaternion LmToBullet(const LMQuaternion& LMQuaternion) {
	return btQuaternion((float) LMQuaternion.GetX(), (float) LMQuaternion.GetY(), (float) LMQuaternion.GetZ(), (float) LMQuaternion.GetW());
}
// Converts an Ogre quaternion to LMQuaternion
LMQuaternion OgreToLm(const Ogre::Quaternion& ogreQuaternion) {
	return LMQuaternion(ogreQuaternion.w, ogreQuaternion.x, ogreQuaternion.y, ogreQuaternion.z);
}
// Converts an LMQuaternion to an Ogre quaternion
Ogre::Quaternion LmToOgre(const LMQuaternion& LMQuaternion) {
	return Ogre::Quaternion((float) LMQuaternion.GetW(), (float) LMQuaternion.GetX(), (float) LMQuaternion.GetY(), (float) LMQuaternion.GetZ());
}
// Converts a Bullet transform to LMQuaternion
LMQuaternion BullTransformToLm(btTransform bulletTransform) {
	return LMQuaternion(bulletTransform.getRotation().w(), bulletTransform.getRotation().x(), bulletTransform.getRotation().y(), bulletTransform.getRotation().z());
}
// Converts an LMQuaternion to a Bullet Transform
btTransform LmToBullTransform(LMQuaternion LMQuaternion) {
	btTransform bulletTransform;
	bulletTransform.setIdentity();
	bulletTransform.setRotation(LmToBullet(LMQuaternion));
	return bulletTransform;
}
// Converts an lmVector and LMQuaternion to a Bullet Transform
btTransform LmToBullTransform(LMVector3 lmVector, LMQuaternion LMQuaternion) {
	btTransform bulletTransform;
	bulletTransform.setIdentity();
	bulletTransform.setOrigin(LmToBullet(lmVector));
	bulletTransform.setRotation(LmToBullet(LMQuaternion));
	return bulletTransform;
}
