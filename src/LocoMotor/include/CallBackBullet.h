#pragma once
class btPersistentManifold;
class btManifoldPoint;
class btPersistentManifold;

void LMcontactStart(btPersistentManifold* const& manifold);
bool LMcontactProcessed(btManifoldPoint& cp, void* body0, void* body1);
void LMcontactExit(btPersistentManifold* const& manifold);