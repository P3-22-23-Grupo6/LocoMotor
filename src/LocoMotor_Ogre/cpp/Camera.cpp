#include "Camera.h"

OgreWrapper::Camera::Camera(Ogre::Camera* camera, Ogre::SceneNode* node)
{
	mNode = node;
	mCamera = camera;
}

OgreWrapper::Camera::~Camera()
{
}
