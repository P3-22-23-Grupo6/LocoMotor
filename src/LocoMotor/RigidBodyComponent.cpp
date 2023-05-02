#include "RigidBodyComponent.h"
#include "LMVector.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer3D.h"
#include "MeshRenderer.h"
#include "MeshStrider.h"
#include "LmVectorConverter.h"
using namespace PhysicsWrapper;
using namespace LocoMotor;

/**
 * This is the constructor for the RigidBodyComponent class, which initializes its member variables.
 */
LocoMotor::RigidBodyComponent::RigidBodyComponent()
{
	_mass = 0;
	_damping = 0.9f;
	_angDamping = 0.7f;
	_gravity = true;
	_body = nullptr;
	_ms = nullptr;
}

/**
 * The function sets the mass of a rigid body component in a locomotor.
 * @brief Sets the mass of a rigid body component in a locomotor.
 * @param mass The mass of the rigid body component of a locomotor.
 */
void LocoMotor::RigidBodyComponent::Start(float mass)
{
	_mass = mass;
}

/**
 * This function deletes the motion state, collision shape, and body of a rigid body component and
 * removes it from the physics world.
 */
LocoMotor::RigidBodyComponent::~RigidBodyComponent() {
	delete _ms;
	PhysicsManager::GetInstance()->RemoveRigidBodyFromWorld(_body);
	if (_body && _body->getMotionState()) {
		delete _body->getMotionState();
	}
	delete _body->getCollisionShape();
	delete _body;
}

/**
 * The function adds a force to a rigid body component using the Bullet physics engine.
 * @brief Adds a force to a rigid body component using the Bullet physics engine.
 * @param force The force vector that is being applied to the rigid body component.
 */
void LocoMotor::RigidBodyComponent::addForce(LMVector3 force)
{
	_body->applyCentralForce(LmToBullet(force));
}

/**
 * The function creates a rigid body for a game object based on its mass and mesh renderer, if
 * applicable.
 * 
 */
void LocoMotor::RigidBodyComponent::PreStart() {
	
	RigidBodyInfo info;
	info.mass = _mass;
	info.boxSize = LmToBullet(LMVector3(0,0,0));
	info.origin = LmToBullet(gameObject->GetTransform()->GetPosition());
	info.sphereSize = 5;
	info.capsuleHeight = 10;
	info.capsuleRadius = 3;
	if (_mass == 0) {
		OgreWrapper::Renderer3D* mesh = gameObject->GetComponent<MeshRenderer>()->GetRenderer();
		if (mesh != nullptr) {
			_ms = new MeshStrider(mesh->GetMesh());
			_body = PhysicsManager::GetInstance()->CreateRigidBody(info, _ms);
			_body->setUserPointer(gameObject);
			if (_raycast) UseItAsRaycast();
			//delete ms;
			return;
		}	
	}
	_body = PhysicsManager::GetInstance()->CreateRigidBody(info);
	_body->setUserPointer(gameObject);
	SetCollisionGroup(1);
	SetCollisionMask(1);
	if (_raycast) UseItAsRaycast();
}


/**
 * The function initializes the parameters of a rigid body component based on a vector of pairs of
 * strings.
 * @brief Initializes the parameters of a rigid body component
 * @param params A vector of pairs where each pair contains a string representing a parameter name and
 * a string representing the parameter value.
 */
void LocoMotor::RigidBodyComponent::Init(std::vector<std::pair<std::string, std::string>>& params) {
	for (int i = 0; i < params.size(); i++) {
		if (params[i].first == "mass") {
			_mass = std::stof(params[i].second);
		}
		else if (params[i].first == "damping") {
			_damping = std::stof(params[i].second);
		}
		else if (params[i].first == "angDamping") {
			_angDamping = std::stof(params[i].second);
		}
		else if (params[i].first == "gravity") {
			_gravity = std::stoi(params[i].second);
		}
		else if (params[i].first == "usedAsRaycast") {
			_raycast = true;
		}
	}
	
}

/**
 * The function updates the position and rotation of a game object's rigid body component based on its
 * corresponding Bullet physics body.
 * 
 * @param dt dt stands for delta time, which is the time elapsed since the last frame update. It is
 * used to ensure that the movement of the object is consistent across different frame rates.
 */
void LocoMotor::RigidBodyComponent::Update(float dt) {

	gameObject->SetPosition(BulletToLm(_body->getWorldTransform().getOrigin()));
	gameObject->SetRotation(BulletToLm(_body->getWorldTransform().getRotation()));
	//_body->clearForces(); // :TODO
}


/**
 * This function sets the rotation of a rigid body component using a given quaternion.
 * @brief Sets the rotation of a rigid body component using a given quaternion.
 * @param rot A LMQuaternion representing the desired rotation to set for the RigidBodyComponent.
 */
void LocoMotor::RigidBodyComponent::setRotation(LMQuaternion rot)
{
	_body->getWorldTransform().setRotation(LmToBullet(rot));
}

/**
 * This function sets the position of a rigid body component using a LMVector3 position.
 * @brief Sets the position of a rigid body component using a LMVector3 position.
 * @param pos pos is a 3D vector representing the new position of the rigid body component.
 */
void LocoMotor::RigidBodyComponent::setPosition(LMVector3 pos)
{
	_body->getWorldTransform().setOrigin(LmToBullet(pos));
}

/**
 * The function sets the gravity of a rigid body component using a given vector.
 * @brief Sets the gravity of a rigid body component using a given vector.
 * @param gravity A vector representing the gravitational force to be applied to the rigid body
 * component.
 */
void LocoMotor::RigidBodyComponent::useGravity(LMVector3 gravity) {

	_body->setGravity(LmToBullet(gravity));
}

/**
 * The function freezes the position of a rigid body along a specified axis.
 * @brief Freezes the position of a rigid body along a specified axis.
 * @param freezeAxis A vector that represents the axis along which the position of the rigid body
 * should be frozen.
 */
void LocoMotor::RigidBodyComponent::FreezePosition(LMVector3 freezeAxis) {
	_body->setLinearFactor(LmToBullet(freezeAxis));
}

/**
 * This function freezes the rotation of a rigid body along a specified axis in a game engine using
 * Bullet physics.
 * @brief Freezes the rotation of a rigid body along a specified axis.
 * @param freezeAxis A vector that represents the axis along which the rotation of the rigid body
 * should be frozen.
 */
void LocoMotor::RigidBodyComponent::FreezeRotation(LMVector3 freezeAxis) {
	_body->setAngularFactor(LmToBullet(freezeAxis));
}

/**
 * This function checks if the rigid body component of a game object collides with another game
 * object's rigid body component.
 * @brief Checks if the rigid body component of a game object collides with another
 * @param other The parameter "other" is a pointer to a GameObject object, which is being checked for
 * collision with the current object's RigidBodyComponent.
 * 
 * @return a boolean value. It returns true if the rigid body component of the current game object
 * collides with the rigid body component of the other game object passed as a parameter, and false
 * otherwise.
 */
bool LocoMotor::RigidBodyComponent::checkCollision(GameObject* other) {
	if (other != nullptr) {
		return _body->checkCollideWith(other->GetComponent<RigidBodyComponent>()->getBody());
	}
	return false;
}

/**
 * The function returns the rigid body component of a locomotor.
 * @brief Returns the rigid body component of a locomotor.
 * @return a pointer to a btRigidBody object, which is the physics body component of the LocoMotor.
 */
btRigidBody* LocoMotor::RigidBodyComponent::getBody() {
	return _body;
}
/**
 * The function sets a collision flag for a rigid body component to disable contact response.
 * @brief Disable contact response for a rigid body component, mantaining the collision
 */
void LocoMotor::RigidBodyComponent::beATrigger()
{
	_body->setCollisionFlags(_body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
}


/**
 * This function checks if a raycast from a starting point to an ending point hits any objects in the
 * physics simulation.
 * @brief Checks if a raycast hits any objects in the physics simulation.
 * @param from The starting point of the raycast in 3D space.
 * @param to The "to" parameter is a 3D vector representing the end point of the raycast. It is the
 * point in space where the raycast ends and checks for collisions or intersections with objects in the
 * scene.
 * 
 * @return A boolean value indicating whether a raycast from the "from" point to the "to" point has hit
 * any objects in the physics simulation.
 */
bool LocoMotor::RigidBodyComponent::GetRaycastHit(LMVector3 from, LMVector3 to) {
	return PhysicsManager::GetInstance()->createRaycast(from,to).hasHit;
}

/**
 * This function returns the point of intersection between a ray cast from a starting point to an
 * ending point and any objects in the scene.
 * @brief Returns the point of intersection between a ray cast and any objects in the scene.
 * @param from The starting point of the raycast, represented as a 3D vector.
 * @param to The "to" parameter is the end point of the raycast, which is the point in 3D space where
 * the ray ends or terminates.
 * 
 * @return a LMVector3, which is the position of the raycast hit point between the two given points
 * "from" and "to".
 */
LMVector3 LocoMotor::RigidBodyComponent::GetraycastHitPoint(LMVector3 from, LMVector3 to) {
	return PhysicsManager::GetInstance()->createRaycast(from, to).hitPos;
}

/**
 * This function returns the normal vector of the raycast hit between two given points.
 * @brief Returns the normal vector of the raycast hit between two given points.
 * @param from The starting point of the raycast in 3D space. It is a LMVector3 data type, which
 * represents a 3D vector with x, y, and z components.
 * @param to The "to" parameter is a 3D vector representing the end point of the raycast. It is the
 * point in space where the raycast ends or terminates.
 * 
 * @return a LMVector3 which represents the normal vector of the surface that was hit by a raycast
 * created by the PhysicsManager instance. The raycast is created between two points, "from" and "to".
 */
LMVector3 LocoMotor::RigidBodyComponent::GethasRaycastHitNormal(LMVector3 from, LMVector3 to){
	return PhysicsManager::GetInstance()->createRaycast(from, to).hitVNormal;
}

/**
 * This function sets the collision group of a rigid body component.
 * @brief Sets the collision group of a rigid body component.
 * @param group The integer value representing the collision group that the rigid body component
 * belongs to. This is used in collision detection to determine which objects can collide with each
 * other based on their assigned collision groups.
 */
void LocoMotor::RigidBodyComponent::SetCollisionGroup(int group)
{
	btBroadphaseProxy* proxy= _body->getBroadphaseProxy();
	proxy->m_collisionFilterGroup = group;
}

/**
 * This function returns the collision group of a rigid body component
 * @brief Returns the collision group of a rigid body component.
 * @return The collision filter group of the rigid body component's broadphase proxy.
 */
int LocoMotor::RigidBodyComponent::GetCollisionGroup()
{
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	return proxy->m_collisionFilterGroup;
}

/**
 * The function sets the collision filter mask of a rigid body component
 * @brief Sets the collision filter mask of a rigid body component.
 * @param mask The parameter "mask" is an integer value that represents the collision filter mask to be
 * set for the rigid body component. This mask is used to determine which collision groups the rigid
 * body should collide with and which ones it should ignore. The value of the mask is typically a bit
 * flag that is used to
 */
void LocoMotor::RigidBodyComponent::SetCollisionMask(int mask)
{
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	proxy->m_collisionFilterMask = 1<<mask;
}

/**
 * This function returns the collision mask of a rigid body component.
 * @brief Returns the collision mask of a rigid body component.
 * @return The collision filter mask of the rigid body component's broadphase proxy.
 */
int LocoMotor::RigidBodyComponent::GetCollisionMask()
{
	btBroadphaseProxy* proxy = _body->getBroadphaseProxy();
	return proxy->m_collisionFilterMask;
}

/**
 * The function returns the linear velocity of a rigid body in a game engine.
 * @brief Returns the linear velocity of a rigid body in a game engine.
 * @return A LMVector3 object representing the linear velocity of the rigid body component.
 */
LMVector3 LocoMotor::RigidBodyComponent::GetLinearVelocity() {
	return BulletToLm(_body->getLinearVelocity()) ;
}
void LocoMotor::RigidBodyComponent::SetLinearVelocity(LMVector3 newLinearVelocity) {
	_body->setLinearVelocity(LmToBullet(newLinearVelocity));
}

/**
 * This function returns the total torque of a rigid body in a game engine, converted from Bullet
 * physics engine format to the game engine's format.
 * @brief Returns the total torque of a rigid body in a game engine.
 * @return A LMVector3 object representing the total torque of the rigid body component
 */
LMVector3 LocoMotor::RigidBodyComponent::GetTotalTorque() {
	return BulletToLm(_body->getTotalTorque());
}

/**
 * This function returns the turn velocity of a rigid body component in a game engine.
 * @brief Returns the turn velocity of a rigid body component in a game engine.
 * @return A LMVector3 object representing the turn velocity of the rigid body component.
 */
LMVector3 LocoMotor::RigidBodyComponent::GetTurnVelocity() {
	return BulletToLm(_body->getTurnVelocity());
}

/**
 * This function returns the angular velocity of a rigid body in a game engine.
 * @brief Returns the angular velocity of a rigid body in a game engine.
 * @return A LMVector3 object representing the angular velocity of the rigid body component.
 */
LMVector3 LocoMotor::RigidBodyComponent::GetAngularVelocity() {
	return BulletToLm(_body->getAngularVelocity());
}

/**
 * This function sets the angular velocity of a rigid body component using a given LMVector3 value.
 * @brief Sets the angular velocity of a rigid body component using a given LMVector3 value.
 * @param newAngularVelocity newAngularVelocity is a LMVector3 variable that represents the new angular
 * velocity to be set for the rigid body component.
 */
void LocoMotor::RigidBodyComponent::SetAngularVelocity(LMVector3 newAngularVelocity) {
	_body->setAngularVelocity(LmToBullet(newAngularVelocity));
}

/**
 * The function applies a torque impulse to a rigid body component using a given vector.
 * @brief Applies a torque impulse to a rigid body component using a given vector.
 * @param impulse The impulse is a vector that represents the amount and direction of the force applied
 * to the rigid body to cause it to rotate around its center of mass. In this case, the impulse is
 * being applied as a torque impulse, which means it will cause the body to rotate around its axis.
 */
void LocoMotor::RigidBodyComponent::ApplyTorqueImpulse(LMVector3 impulse) {
	_body->applyTorqueImpulse(LmToBullet(impulse));
}

/**
 * The function sets the friction of a rigid body component in a physics engine.
 * @brief Sets the friction of a rigid body component in a physics engine.
 * @param fric fric is a float variable representing the friction coefficient to be set for the rigid
 * body component. The friction coefficient determines the amount of friction between two surfaces in
 * contact, and affects the body's ability to move or rotate. A higher friction coefficient means more
 * resistance to movement, while a lower coefficient means less
 */
void LocoMotor::RigidBodyComponent::SetFriction(float fric) {
	_body->setFriction(fric);
}

void LocoMotor::RigidBodyComponent::UseItAsRaycast() {
	SetCollisionGroup(10);
}

void LocoMotor::RigidBodyComponent::SetActivationState(ActiveState newState) {
	_body->setActivationState(newState);
}
