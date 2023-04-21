#pragma once
#include "btBulletDynamicsCommon.h"
struct ClosestRayCallbackBullet : public btCollisionWorld::RayResultCallback {
	ClosestRayCallbackBullet(const btVector3& rayFromWorld, const btVector3& rayToWorld)
		: m_rayFromWorld(rayFromWorld),
		m_rayToWorld(rayToWorld) {
	}

	btVector3 m_rayFromWorld;  //used to calculate hitPointWorld from hitFraction
	btVector3 m_rayToWorld;

	btVector3 m_hitNormalWorld;
	btVector3 m_hitPointWorld;

	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) {
		//caller already does the filter on the m_closestHitFraction
		btAssert(rayResult.m_hitFraction <= m_closestHitFraction);

		m_closestHitFraction = rayResult.m_hitFraction;
		int group = rayResult.m_collisionObject->getBroadphaseHandle()->m_collisionFilterGroup;
		if (group == 2)
		m_collisionObject = rayResult.m_collisionObject;
		
		if (normalInWorldSpace) {
			m_hitNormalWorld = rayResult.m_hitNormalLocal;
		}
		else {
			///need to transform normal into worldspace
			m_hitNormalWorld = m_collisionObject->getWorldTransform().getBasis() * rayResult.m_hitNormalLocal;
		}
		m_hitPointWorld.setInterpolate3(m_rayFromWorld, m_rayToWorld, rayResult.m_hitFraction);
		return rayResult.m_hitFraction;
	}
};