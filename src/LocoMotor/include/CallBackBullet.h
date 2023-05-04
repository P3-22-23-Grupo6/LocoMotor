#pragma once
class btPersistentManifold;
class btManifoldPoint;
class btPersistentManifold;

namespace LocoMotor {
	/// @brief Indicates how has to act the physics when entering a collision trigger
	void LMcontactStart(btPersistentManifold* const& manifold);
	/// @brief Indicates how has to act the physics when staying a collision trigger
	bool LMcontactProcessed(btManifoldPoint& cp, void* body0, void* body1);
	/// @brief Indicates how has to act the physics when exiting a collision trigger
	void LMcontactExit(btPersistentManifold* const& manifold);
}
