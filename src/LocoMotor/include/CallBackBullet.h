#pragma once
class btPersistentManifold;
class btManifoldPoint;
class btPersistentManifold;

void contactStartBullet(btPersistentManifold* const& manifold);
bool contactProcessedBullet(btManifoldPoint& cp, void* body0, void* body1);
void contactExitBullet(btPersistentManifold* const& manifold);