#include "LMGameObject.h"
#include <btBulletDynamicsCommon.h>


LMGameObject::LMGameObject (Ogre::SceneManager* sceneMgr, btDiscreteDynamicsWorld* dynamicsWorld, FMOD::System* audioSystem) :
    _mSceneMgr (sceneMgr),
    _mPhysicsWorld (dynamicsWorld),
    _mAudioSystem (audioSystem) {
    // Create default transform
    _mTransform = new btTransform (LMQuaternion::LmToBullet(LMQuaternion()), LMVector3::LmToBullet (LMVector3 ()));

    // Set default collision shape and rigid body
    btCollisionShape* colShape = new btBoxShape (btVector3 (1, 1, 1));
    btScalar mass = 1.0;
    btVector3 localInertia (0, 0, 0);
    colShape->calculateLocalInertia (mass, localInertia);
    btDefaultMotionState* motionState = new btDefaultMotionState (btTransform (btQuaternion (0, 0, 0, 1), btVector3 (0, 0, 0)));
    btRigidBody::btRigidBodyConstructionInfo rbInfo (mass, motionState, colShape, localInertia);
    _mRigidBody = new btRigidBody (rbInfo);

    // Set default sound effect
    /*FMOD::Sound* sound = nullptr;
    FMOD_RESULT result = audioSystem->createSound ("default_sound.wav", FMOD_DEFAULT, nullptr, &sound);
    if (result == FMOD_OK) {
        mSoundEffect = sound;
    }*/
}

LMGameObject::~LMGameObject () {
    // Remove rigid body from dynamics world
    _mPhysicsWorld->removeRigidBody (_mRigidBody);

    // Delete rigid body and collision shape
    delete _mRigidBody->getMotionState ();
    delete _mRigidBody->getCollisionShape ();
    delete _mRigidBody;

    // Release sound effect
    /*if (_mSoundEffect) {
        mSoundEffect->release ();
    }*/
}

void LMGameObject::setPosition (LMVector3 pos) {
    
    _mRigidBody->getWorldTransform ().setOrigin (LMVector3::LmToBullet(pos));
}

LMVector3 getPosition () const {
    return mTransform.getPosition ();
}

void setOrientation (LMQuaternion quat) {
    mTransform.setOrientation (quat);
    mRigidBody->getWorldTransform ().setRotation (btQuaternion (quat.x, quat.y, quat.z, quat.w));
}

LMQuaternion getOrientation () const {
    return mTransform.getOrientation ();
}

void setScale (LMVector3 scale) {
    mTransform.setScale (scale);
}

Ogre::Vector3 getScale () const {
    return mTransform.getScale ();
}

void setMass (float mass) {
    btVector3 localInertia (0, 0, 0);
    mRigidBody->getCollisionShape ()->calculateLocalInertia (mass, localInertia);
    mRigidBody->setMassProps (mass, localInertia);
}

float getMass () const {
    return mRigidBody->getMass ();
}

void setSoundEffect (const std::string& filename) {
    FMOD::Sound* sound = nullptr;
    FMOD_RESULT result = mAudioSystem->createSound (filename.c_str (), FMOD_DEFAULT, nullptr, &sound);
    if (result == FMOD_OK) {
        if (mSoundEffect) {
            mSoundEffect->release ();
        }
        mSoundEffect = sound;
    }
}
