#include "Camera.h"

#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include "OgreManager.h"
#include <OgreRenderWindow.h>
#include <OgreVector3.h>

int OgreWrapper::Camera::_zOrder = 0;

OgreWrapper::Camera::Camera(Ogre::Camera* camera) {
	_mCamera = camera;
	_mCamera->setAutoAspectRatio(true);
	//_mCamera->setPolygonMode(Ogre::PM_WIREFRAME);
	_mZOrder = Camera::_zOrder;
	//Normal Camera
	_vp = OgreWrapper::OgreManager::GetInstance()->GetRenderWindow()->addViewport(_mCamera, Camera::_zOrder);
	Camera::_zOrder++;
	_vp->setBackgroundColour(Ogre::ColourValue(0.6f, 0.7f, 0.8f));
}

OgreWrapper::Camera::~Camera() {
	//int _zOrder;
}

Ogre::Viewport* OgreWrapper::Camera::GetViewport() {
	return _vp;
}

Ogre::MovableObject* OgreWrapper::Camera::GetMovObj() {
	return _mCamera;
}

void OgreWrapper::Camera::SetAspectRatio(Ogre::Real ratio) {
	_mCamera->setAspectRatio(ratio);
}

void OgreWrapper::Camera::SetFOV(float newFOV) {
	_mCamera->setFOVy(Ogre::Radian(newFOV * 3.14f / 180));//Conversion Provisional, meter en LMVector o LMQuaternion
}

void OgreWrapper::Camera::SetViewportRatio(int viewportIndex, int modeIndex) {
	if (modeIndex == 0) {
		GetViewport()->setDimensions(0.0f, 0.0f, 1.0f, 1.0f);
		SetAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}
	else if (modeIndex == 1) {
		GetViewport()->setDimensions(0.0f, 0.0f, 1.0f, 0.5f);
		GetViewport()->update();
		SetAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}
	else if (modeIndex == 2) {
		GetViewport()->setDimensions(0.0f, 0.5f, 1.0f, 0.5f);
		GetViewport()->update();
		SetAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}

}

void OgreWrapper::Camera::SetTracking(bool shouldTrack, Ogre::SceneNode* nodeToTrack, const Ogre::Vector3& offset) {
}

void OgreWrapper::Camera::SetClippingPlane(Ogre::Real nearDis, Ogre::Real farDis) {
	_mCamera->setNearClipDistance(nearDis);
	_mCamera->setFarClipDistance(farDis);
}

void OgreWrapper::Camera::Render() {
	_vp->update();
}
