#include "Node.h"

#include <OgreSceneNode.h>
#include <OgreMovableObject.h>
#include <OgreNode.h>

OgreWrapper::Node::Node (Ogre::SceneNode* node) {
	_node = node;
}

OgreWrapper::Node::~Node () {
}

void OgreWrapper::Node::Translate (float x, float y, float z) {
	_node->translate (x, y, z, Ogre::Node::TS_WORLD);
}

void OgreWrapper::Node::Rotate (float x, float y, float z) {
	_node->pitch (Ogre::Degree (x));
	_node->yaw (Ogre::Degree (y));
	_node->roll (Ogre::Degree (z));
}

void OgreWrapper::Node::Scale (float x, float y, float z) {
	_node->scale (x, y, z);
}

void OgreWrapper::Node::Attach (Ogre::MovableObject* obj) {
	_node->attachObject (obj);
}

