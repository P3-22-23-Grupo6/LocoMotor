#include "Node.h"

#include <OgreSceneNode.h>
#include <OgreMovableObject.h>
#include <OgreNode.h>
#include "RenderEntity.h"

OgreWrapper::Node::Node(Ogre::SceneNode* node) {
	_node = node;
	_ent = std::vector<OgreWrapper::RenderEntity*>();
}

OgreWrapper::Node::~Node() {
	for (std::vector<OgreWrapper::RenderEntity*>::iterator it = _ent.begin(); it != _ent.end(); it = _ent.erase(it)) {
		delete* it;
	}
}

void OgreWrapper::Node::Translate(float x, float y, float z) {
	_node->translate(x, y, z, Ogre::Node::TS_LOCAL);
}

void OgreWrapper::Node::Rotate(float x, float y, float z) {
	_node->pitch(Ogre::Degree(x));
	_node->yaw(Ogre::Degree(y));
	_node->roll(Ogre::Degree(z));
}

void OgreWrapper::Node::RotateLocal(float x, float y, float z) {
	_node->pitch(Ogre::Degree(x), Ogre::Node::TS_LOCAL);
	_node->yaw(Ogre::Degree(y), Ogre::Node::TS_LOCAL);
	_node->roll(Ogre::Degree(z), Ogre::Node::TS_LOCAL);
}

void OgreWrapper::Node::Scale(float x, float y, float z) {
	_node->scale(x, y, z);
}

void OgreWrapper::Node::LookAt(float x, float y, float z) {
	_node->lookAt(Ogre::Vector3(x, y, z), Ogre::Node::TS_WORLD);
}

void OgreWrapper::Node::SetDirection(float x, float y, float z) {
	_node->setDirection(x, y, z);
}

void OgreWrapper::Node::Attach(OgreWrapper::RenderEntity* obj) {
	
	_node->attachObject(obj->GetMovObj());
	_ent.push_back (obj);
}

OgreWrapper::Node* OgreWrapper::Node::CreateChild() {
	Node* child = new Node(_node->createChildSceneNode());
	return child;
}


void OgreWrapper::Node::SetPosition(float x, float y, float z) {
	_node->setPosition(x, y, z);
}

float OgreWrapper::Node::GetPosition_X() {
	return _node->getPosition().x;
}

float OgreWrapper::Node::GetPosition_Y() {
	return _node->getPosition().y;
}

float OgreWrapper::Node::GetPosition_Z() {
	return _node->getPosition().z;
}

void OgreWrapper::Node::SetScale(float x, float y, float z) {
	_node->setScale(x, y, z);
}

void OgreWrapper::Node::ResetOrientation() {
	_node->resetOrientation();
}

void OgreWrapper::Node::SetOrientation(Ogre::Quaternion& q) {
	_node->setOrientation(q.w, q.x, q.y, q.z);
}
