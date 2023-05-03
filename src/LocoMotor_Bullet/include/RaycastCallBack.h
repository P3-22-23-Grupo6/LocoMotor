#pragma once
#include "btBulletDynamicsCommon.h"
//Callback when try to calculate a Raycast , original code in Bullet
struct ClosestRayCallbackBullet : public btCollisionWorld::RayResultCallback {
	ClosestRayCallbackBullet(const btVector3& rayFromWorld, const btVector3& rayToWorld)
		: m_rayFromWorld(rayFromWorld),
		m_rayToWorld(rayToWorld) {
	}

	btVector3 m_rayFromWorld;
	btVector3 m_rayToWorld;

	btVector3 m_hitNormalWorld;
	btVector3 m_hitPointWorld;

	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) {
		btAssert(rayResult.m_hitFraction <= m_closestHitFraction);
		m_closestHitFraction = rayResult.m_hitFraction;
		int group = rayResult.m_collisionObject->getBroadphaseHandle()->m_collisionFilterGroup;
		//Only raycast a determinate group of collision objects
		if (group == 10) {
			m_collisionObject = rayResult.m_collisionObject;
		}
		else {
			m_collisionObject = 0;
		}
		if (normalInWorldSpace) {
			m_hitNormalWorld = rayResult.m_hitNormalLocal;
		}
		else {
			m_hitNormalWorld = m_collisionObject->getWorldTransform().getBasis() * rayResult.m_hitNormalLocal;
		}
		m_hitPointWorld.setInterpolate3(m_rayFromWorld, m_rayToWorld, rayResult.m_hitFraction);
		return rayResult.m_hitFraction;
	}
};