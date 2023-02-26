#include "Camera.h"

#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include "OgreManager.h"
#include <OgreRenderWindow.h>

OgreWrapper::Camera::Camera(Ogre::Camera* camera, Ogre::SceneNode* node):Node(node)
{
	mCamera = camera;
	mCamera->setNearClipDistance (1);
	mCamera->setFarClipDistance (10000);
	mCamera->setAutoAspectRatio (true);
	//mCamera->setPolygonMode(Ogre::PM_WIREFRAME);

	vp = OgreWrapper::OgreManager::GetInstance()->GetRenderWindow()->addViewport(mCamera);
	vp->setBackgroundColour (Ogre::ColourValue (0.6, 0.7, 0.8));
}

OgreWrapper::Camera::~Camera()
{
}

void OgreWrapper::Camera::LookAt(const Ogre::Vector3& targetPoint)
{
	_node->lookAt(targetPoint, Ogre::Node::TS_WORLD);
}

void OgreWrapper::Camera::Render () {
	vp->update ();
}
