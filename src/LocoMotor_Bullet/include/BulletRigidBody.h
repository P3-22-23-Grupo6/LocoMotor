#pragma once
#ifndef _BULLETRIGIDBODY_H_
#define _BULLETRIGIDBODY_H_

class btRigidBody;
class btCollisionShape;
class btVector3;
class LMQuaternion;
namespace PhysicsWrapper {
	struct RigidBodyInfo;
	//class BulletManager;
	class BulletRigidBody {
	public:
		BulletRigidBody(RigidBodyInfo info);
		~BulletRigidBody();
		void AddForce(btVector3 force);
		void setRotation(LMQuaternion rot);
		LMQuaternion getRotation();
	private:
		btRigidBody* _rigidBody = nullptr;
		btCollisionShape* _shape = nullptr;
	};
}


#endif