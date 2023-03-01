#include "Ogre.h"
#include "FMod.h"
#include "lmVector.h"
class btVector3;
class btTransform;
class btQuaternion;
class btDiscreteDynamicsWorld;


class LMGameObject {


public:
	LMGameObject (Ogre::SceneManager* sceneMgr, btDiscreteDynamicsWorld* dynamicsWorld, FMOD::System* audioSystem);

	virtual ~LMGameObject ();

	void setPosition(LMVector3 pos);

	LMVector3 getPosition() const;

	void setOrientation(LMQuaternion quat);

	LMQuaternion getOrientation() const;

	void setScale(LMVector3 scale);

	LMVector3 getScale() const;

	void setCollisionShape(btCollisionShape* shape);

	btCollisionShape* getCollisionShape() const;

	void setRigidBody(btRigidBody* body);

	btRigidBody* getRigidBody() const;

	void setSoundEffect(FMOD::Sound* sound);

	FMOD::Sound* getSoundEffect() const;

	void setSoundChannel(FMOD::Channel* channel);

	FMOD::Channel* getSoundChannel() const;

private:
	Ogre::SceneManager* _mSceneMgr;
	Ogre::SceneNode* _mSceneNode;
	Ogre::Entity* _mEntity;
	btDiscreteDynamicsWorld* _mPhysicsWorld;
	btRigidBody* _mRigidBody;
	btTransform* _mTransform;
	FMOD::System* mAudioSystem;
	FMOD::Sound* mSound;
	FMOD::Channel* mChannel;

};