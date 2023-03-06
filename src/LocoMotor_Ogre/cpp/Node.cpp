#include "Node.h"

#include <OgreSceneNode.h>
#include <OgreMovableObject.h>
#include <OgreNode.h>
#include "RenderEntity.h"

OgreWrapper::Node::Node(Ogre::SceneNode* node) {
	_node = node;
	_ent = nullptr;
}

OgreWrapper::Node::~Node() {
	if (_ent != nullptr) delete _ent;
}

void OgreWrapper::Node::Translate(float x, float y, float z) {
	_node->translate(x, y, z, Ogre::Node::TS_LOCAL);
}

void OgreWrapper::Node::Rotate(float x, float y, float z) {
	_node->pitch(Ogre::Degree(x));
	_node->yaw(Ogre::Degree(y));
	_node->roll(Ogre::Degree(z));
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
	if (_ent != nullptr) {
		_node->detachObject(_ent->GetMovObj());
		delete _ent;
	}
	_node->attachObject(obj->GetMovObj());
	_ent = obj;
}

OgreWrapper::Node* OgreWrapper::Node::CreateChild() {
	Node* child = new Node(_node->createChildSceneNode());
	return child;
}


void OgreWrapper::Node::SetPosition(float x, float y, float z) {
	_node->setPosition(x, y, z);
}

void OgreWrapper::Node::SetScale(float x, float y, float z) {
	_node->setScale(x, y, z);
}


