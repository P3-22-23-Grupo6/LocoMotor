#include "Camera.h"
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include "OgreManager.h"
#include <OgreRenderWindow.h>
#include <OgreVector3.h>

OgreWrapper::Camera::Camera(Ogre::Camera* camera) {
	_mCamera = camera;
	_mCamera->setAutoAspectRatio(true);

	//Normal Camera
	OgreWrapper::OgreManager* ogreMng = OgreWrapper::OgreManager::GetInstance();
	int zOrder = ogreMng->GetLastCamIndex(true);

	_vp = ogreMng->GetRenderWindow()->addViewport(_mCamera, zOrder);
	if (zOrder > 1) _vp->setClearEveryFrame(false);
	_vp->setBackgroundColour(Ogre::ColourValue(0.6f, 0.7f, 0.8f));
	_vp->setSkiesEnabled(true);
	_vp->setShadowsEnabled(false);
}

OgreWrapper::Camera::~Camera() {
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

void OgreWrapper::Camera::SetViewportRatio(int camerMode) {
	if (camerMode == 0) {
		GetViewport()->setDimensions(0.0f, 0.0f, 1.0f, 1.0f);
		SetAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}
	else if (camerMode == 1) {
		GetViewport()->setDimensions(0.0f, 0.0f, 1.0f, 0.5f);
		GetViewport()->update();
		SetAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}
	else if (camerMode == 2) {
		GetViewport()->setDimensions(0.0f, 0.5f, 1.0f, 0.5f);
		GetViewport()->update();
		SetAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
	}

}

void OgreWrapper::Camera::SetClippingPlane(Ogre::Real nearDis, Ogre::Real farDis) {
	_mCamera->setNearClipDistance(nearDis);
	_mCamera->setFarClipDistance(farDis);
}

void OgreWrapper::Camera::Render() {
	_vp->update();
}

Ogre::Camera* OgreWrapper::Camera::GetOgreCamera()
{
	return _mCamera;
}
