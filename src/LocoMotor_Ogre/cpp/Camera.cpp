#include "Camera.h"

#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include "OgreManager.h"
#include <OgreRenderWindow.h>
#include <OgreVector3.h>

int OgreWrapper::Camera::_zOrder = 0;

OgreWrapper::Camera::Camera(Ogre::Camera* camera, int cameraMode) {
	_mCamera = camera;
	_mCamera->setNearClipDistance(1);
	_mCamera->setFarClipDistance(10000);
	_mCamera->setAutoAspectRatio(true);
	//mCamera->setPolygonMode(Ogre::PM_WIREFRAME);
	_mZOrder = Camera::_zOrder;
	//Normal Camera
	if(cameraMode == 0) 
		vp = OgreWrapper::OgreManager::GetInstance()->GetRenderWindow()->addViewport(_mCamera, Camera::_zOrder);
	//Camera Left 2 Player Mode
	else if (cameraMode == 1) {
		vp = OgreWrapper::OgreManager::GetInstance()->GetRenderWindow()->addViewport(_mCamera, 0.0, 0.0, 0.0, 0.5, 1.0);
		SetAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	}	
	//Camera Right 2 Player Mode
	else if (cameraMode == 2) {
		vp = OgreWrapper::OgreManager::GetInstance()->GetRenderWindow()->addViewport(_mCamera, 0.0, 0.0, 0.0, 0.5, 1.0);
		SetAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	}
	Camera::_zOrder++;
	vp->setBackgroundColour(Ogre::ColourValue(0.6f, 0.7f, 0.8f));
}

OgreWrapper::Camera::~Camera() {
	//int _zOrder;
}

Ogre::Viewport* OgreWrapper::Camera::GetViewport() {
	return vp;
}

Ogre::MovableObject* OgreWrapper::Camera::GetMovObj() {
	return _mCamera;
}

void OgreWrapper::Camera::SetAspectRatio(Ogre::Real ratio) {
	_mCamera->setAspectRatio(ratio);
}

void OgreWrapper::Camera::Render() {
	vp->update();
}
